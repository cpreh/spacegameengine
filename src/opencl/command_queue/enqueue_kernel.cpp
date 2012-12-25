/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/exception.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <sge/src/opencl/event/flatten_sequence.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/io/ostringstream.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{
typedef
fcppt::container::raw_vector<std::size_t>
size_vector;

typedef
fcppt::optional<size_vector>
optional_size_vector;

fcppt::string const
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
	FCPPT_ASSERT_PRE(
		!work_dim || global_dim.size() == work_dim->size());

	for(std::size_t i = 0; i < global_dim.size(); ++i)
		if(global_dim[i] == 0 || (work_dim && (*work_dim)[i] == 0))
			throw sge::exception(
				FCPPT_TEXT("Neither global nor work dimensions can be zero in any component"));

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
			work_dim
			?
				work_dim->data()
			:
				0,
			static_cast<cl_uint>(
				_events.size()),
			_events.empty()
			?
				0
			:
				sge::opencl::event::flatten_sequence(
					_events).data(),
			&(result->handle()));

	if(error_code == CL_INVALID_WORK_GROUP_SIZE)
	{
		throw
			sge::exception(
				FCPPT_TEXT("Error enqueuing kernel \"")+
				fcppt::from_std_string(
					_kernel.name())+
				FCPPT_TEXT("\": workgroup size invalid. The global dimension is ")+
				output_dimension(
					global_dim)+
				(work_dim
				?
					FCPPT_TEXT(", the workgroup dimension is ")+
					output_dimension(
						*work_dim)
				:
					fcppt::string()));
	}

	sge::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueNDRangeKernel(work)"));

	return
		std::move(
			result);
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
	size_vector global_dim(
		_global_dim.get().size());

	std::copy(
		_global_dim.get().begin(),
		_global_dim.get().end(),
		global_dim.begin());

	size_vector local_dim(
		_local_dim.get().size());

	std::copy(
		_local_dim.get().begin(),
		_local_dim.get().end(),
		local_dim.begin());

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
	size_vector global_dim(
		_global_dim.get().size());

	std::copy(
		_global_dim.get().begin(),
		_global_dim.get().end(),
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
