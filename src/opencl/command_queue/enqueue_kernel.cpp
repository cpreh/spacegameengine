/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/core/exception.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/event/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <sge/src/opencl/event/flatten_sequence.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/io/ostringstream.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace
{
typedef
fcppt::container::raw_vector<std::size_t>
size_vector;

typedef
fcppt::optional<size_vector>
optional_size_vector;

fcppt::string
output_dimension(
	size_vector const &a)
{
	fcppt::io::ostringstream ss;

	ss << FCPPT_TEXT("[");

	for(std::size_t i = 0; i < a.size(); ++i)
		if(i == static_cast<std::size_t>(a.size()-1))
			ss << a[i];
		else
			ss << a[i] << FCPPT_TEXT(",");

	ss << FCPPT_TEXT("]");

	return ss.str();
}

sge::opencl::event::object_unique_ptr
enqueue_kernel_internal(
	sge::opencl::command_queue::object &_queue,
	sge::opencl::kernel::object &_kernel,
	size_vector const &global_dim,
	optional_size_vector const &work_dim,
	sge::opencl::event::sequence const &_events)
{
	fcppt::maybe_void(
		work_dim,
		[
			&global_dim
		](
			size_vector const &_work_dim
		)
		{
			FCPPT_ASSERT_PRE(
				_work_dim.size()
				==
				global_dim.size()
			);

			for(
				std::size_t const index
				:
				fcppt::make_int_range_count(
					global_dim.size()
				)
			)
				if(global_dim[index] == 0 || _work_dim[index] == 0)
					// TODO: opencl exception
					throw sge::core::exception(
						FCPPT_TEXT("Neither global nor work dimensions can be zero in any component"));
		}
	);

	sge::opencl::event::object_unique_ptr result(
		fcppt::make_unique_ptr<sge::opencl::event::object>());

	cl_int const error_code =
		clEnqueueNDRangeKernel(
			_queue.impl(),
			_kernel.impl(),
			static_cast<cl_uint>(
				global_dim.size()),
			0, // global work offset (not implemented in 1.1)
			global_dim.data(),
			fcppt::maybe(
				work_dim,
				[]{
					return
						size_vector::const_pointer(
							nullptr
						);
				},
				[](
					size_vector const &_work_dim
				)
				{
					return
						_work_dim.data();
				}
			),
			static_cast<cl_uint>(
				_events.size()),
			_events.empty()
			?
				nullptr
			:
				sge::opencl::event::flatten_sequence(
					_events).data(),
			&(result->handle()));

	if(error_code == CL_INVALID_WORK_GROUP_SIZE)
	{
		throw
			// TODO: opencl exception
			sge::core::exception(
				FCPPT_TEXT("Error enqueuing kernel \"")
				+
				fcppt::from_std_string(
					_kernel.name()
				)
				+
				FCPPT_TEXT("\": workgroup size invalid. The global dimension is "
				)+
				output_dimension(
					global_dim
				)
				+
				fcppt::maybe(
					work_dim,
					[]{
						return
							fcppt::string{};
					},
					[](
						size_vector const &_work_dim
					)
					{
						return
							FCPPT_TEXT(", the workgroup dimension is ")
							+
							output_dimension(
								_work_dim
							);
					}
				)
			);
	}

	sge::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueNDRangeKernel(work)"));

	return
		result;
}

template<typename GlobalDim,typename LocalDim>
sge::opencl::event::object_unique_ptr
enqueue_kernel_templatized(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	GlobalDim const &_global_dim,
	LocalDim const &_local_dim,
	sge::opencl::event::sequence const &_events)
{
	// TODO: Use map here
	size_vector global_dim(
		GlobalDim::value_type::dim_wrapper::value
	);

	{
		auto const &global_storage(
			_global_dim.get().storage()
		);

		std::copy(
			global_storage.begin(),
			global_storage.end(),
			global_dim.begin());
	}

	size_vector local_dim(
		LocalDim::value_type::dim_wrapper::value
	);

	{
		auto const &local_storage(
			_local_dim.get().storage()
		);


		std::copy(
			local_storage.begin(),
			local_storage.end(),
			local_dim.begin());
	}

	return
		enqueue_kernel_internal(
			_command_queue,
			_kernel,
			global_dim,
			optional_size_vector(
				local_dim),
			_events);
}

template<typename GlobalDim>
sge::opencl::event::object_unique_ptr
enqueue_kernel_templatized(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	GlobalDim const &_global_dim,
	sge::opencl::event::sequence const &_events)
{
	// TODO: Use map here
	size_vector global_dim(
		GlobalDim::value_type::dim_wrapper::value
	);

	auto const &storage(
		_global_dim.get().storage()
	);

	std::copy(
		storage.begin(),
		storage.end(),
		global_dim.begin());

	return
		enqueue_kernel_internal(
			_command_queue,
			_kernel,
			global_dim,
			optional_size_vector(),
			_events);
}
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim1 const &_global_dim,
	sge::opencl::command_queue::local_dim1 const &_local_dim,
	sge::opencl::event::sequence const &_events)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_local_dim,
			_events);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim2 const &_global_dim,
	sge::opencl::command_queue::local_dim2 const &_local_dim,
	sge::opencl::event::sequence const &_events)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_local_dim,
			_events);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim3 const &_global_dim,
	sge::opencl::command_queue::local_dim3 const &_local_dim,
	sge::opencl::event::sequence const &_events)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_local_dim,
			_events);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim1 const &_global_dim,
	sge::opencl::event::sequence const &_events)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_events);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim2 const &_global_dim,
	sge::opencl::event::sequence const &_events)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_events);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim3 const &_global_dim,
	sge::opencl::event::sequence const &_events)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_events);
}
