/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opencl/exception.hpp>
#include <sge/opencl/size_type.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/event/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/impl/event/flatten_sequence.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>


template<
	fcppt::math::size_type N
>
sge::opencl::event::object_unique_ptr
enqueue_kernel_internal(
	sge::opencl::command_queue::object &_queue,
	sge::opencl::kernel::object &_kernel,
	fcppt::math::dim::static_<
		sge::opencl::size_type,
		N
	> const &_global_dim,
	fcppt::optional::object<
		fcppt::math::dim::static_<
			sge::opencl::size_type,
			N
		>
	> const &_work_dim,
	sge::opencl::event::sequence const &_events
)
{
	typedef
	fcppt::math::dim::static_<
		sge::opencl::size_type,
		N
	>
	dim_type;

	if(
		fcppt::math::dim::contents(
			_global_dim
		)
		==
		0u
		||
		fcppt::optional::maybe(
			_work_dim,
			fcppt::const_(
				false
			),
			[](
				dim_type const &_dim
			)
			{
				return
					fcppt::math::dim::contents(
						_dim
					)
					==
					0u;
			}
		)
	)
		throw
			sge::opencl::exception{
				FCPPT_TEXT("Neither global nor work dimensions can be zero in any component")
			};

	sge::opencl::event::object_unique_ptr result{
		fcppt::make_unique_ptr<
			sge::opencl::event::object
		>()
	};

	cl_int const error_code{
		clEnqueueNDRangeKernel(
			_queue.impl(),
			_kernel.impl(),
			fcppt::cast::size<
				cl_uint
			>(
				N
			),
			nullptr, // global work offset (not implemented in 1.1)
			_global_dim.storage().data(),
			fcppt::optional::maybe(
				_work_dim,
				[]{
					return
						typename
						dim_type::storage_type::const_pointer{
							nullptr
						};
				},
				[](
					dim_type const &_dim
				)
				{
					return
						_dim.storage().data();
				}
			),
			fcppt::cast::size<
				cl_uint
			>(
				_events.size()
			),
			_events.empty()
			?
				nullptr
			:
				sge::opencl::impl::event::flatten_sequence(
					_events
				).data(),
			&(result->handle())
		)
	};

	if(
		error_code
		==
		CL_INVALID_WORK_GROUP_SIZE
	)
	{
		throw
			sge::opencl::exception(
				FCPPT_TEXT("Error enqueuing kernel \"")
				+
				fcppt::from_std_string(
					_kernel.name()
				)
				+
				FCPPT_TEXT("\": workgroup size invalid. The global dimension is "
				)
				+
				fcppt::insert_to_fcppt_string(
					_global_dim
				)
				+
				fcppt::optional::maybe(
					_work_dim,
					[]{
						return
							fcppt::string{};
					},
					[](
						dim_type const &_dim
					)
					{
						return
							FCPPT_TEXT(", the workgroup dimension is ")
							+
							fcppt::insert_to_fcppt_string(
								_dim
							);
					}
				)
			);
	}

	sge::opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueNDRangeKernel(work)")
	);

	return
		result;
}

template<
	fcppt::math::size_type N,
	typename GlobalDim,
	typename LocalDim
>
sge::opencl::event::object_unique_ptr
enqueue_kernel_templatized(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	fcppt::strong_typedef<
		fcppt::math::dim::static_<
			sge::opencl::size_type,
			N
		>,
		GlobalDim
	> const &_global_dim,
	fcppt::strong_typedef<
		fcppt::math::dim::static_<
			sge::opencl::size_type,
			N
		>,
		LocalDim
	> const &_local_dim,
	sge::opencl::event::sequence const &_events)
{
	return
		enqueue_kernel_internal(
			_command_queue,
			_kernel,
			_global_dim.get(),
			fcppt::optional::make(
				_local_dim.get()
			),
			_events
		);
}

template<
	typename GlobalDim
>
sge::opencl::event::object_unique_ptr
enqueue_kernel_templatized(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	GlobalDim const &_global_dim,
	sge::opencl::event::sequence const &_events
)
{
	return
		enqueue_kernel_internal(
			_command_queue,
			_kernel,
			_global_dim.get(),
			fcppt::optional::object<
				typename
				GlobalDim::value_type
			>(),
			_events
		);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim1 const &_global_dim,
	sge::opencl::command_queue::local_dim1 const &_local_dim,
	sge::opencl::event::sequence const &_events
)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_local_dim,
			_events
		);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim2 const &_global_dim,
	sge::opencl::command_queue::local_dim2 const &_local_dim,
	sge::opencl::event::sequence const &_events
)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_local_dim,
			_events
		);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim3 const &_global_dim,
	sge::opencl::command_queue::local_dim3 const &_local_dim,
	sge::opencl::event::sequence const &_events
)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_local_dim,
			_events
		);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim1 const &_global_dim,
	sge::opencl::event::sequence const &_events
)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_events
		);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim2 const &_global_dim,
	sge::opencl::event::sequence const &_events
)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_events
		);
}

sge::opencl::event::object_unique_ptr
sge::opencl::command_queue::enqueue_kernel(
	sge::opencl::command_queue::object &_command_queue,
	sge::opencl::kernel::object &_kernel,
	sge::opencl::command_queue::global_dim3 const &_global_dim,
	sge::opencl::event::sequence const &_events
)
{
	return
		enqueue_kernel_templatized(
			_command_queue,
			_kernel,
			_global_dim,
			_events
		);
}
