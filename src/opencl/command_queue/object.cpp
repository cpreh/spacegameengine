/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opencl/command_queue/execution_mode.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <fcppt/text.hpp>


sge::opencl::command_queue::object::object(
	opencl::device::object &_device,
	opencl::context::object &_context,
	command_queue::execution_mode::type const execution_mode,
	command_queue::profiling_mode::type const profiling_mode)
:
	context_(
		_context),
	device_(
		_device),
	queue_()
{
	cl_int error_code;

	queue_ =
		clCreateCommandQueue(
			context_.context_,
			device_.device_id_,
			(execution_mode == command_queue::execution_mode::out_of_order
			?
				CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE
			:
				static_cast<cl_command_queue_properties>(0))
			|
			(profiling_mode == command_queue::profiling_mode::enabled)
			?
				CL_QUEUE_PROFILING_ENABLE
			:
				static_cast<cl_command_queue_properties>(0),
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateCommandQueue"));
}

sge::opencl::context::object &
sge::opencl::command_queue::object::context() const
{
	return context_;
}

sge::opencl::device::object &
sge::opencl::command_queue::object::device() const
{
	return device_;
}

cl_command_queue
sge::opencl::command_queue::object::impl() const
{
	return queue_;
}

void
sge::opencl::command_queue::object::finish()
{
	cl_int const finish_error_code = clFinish(
		queue_);

	opencl::handle_error(
		finish_error_code,
		FCPPT_TEXT("clFinish"));
}

sge::opencl::command_queue::object::~object()
{
	/*
	this->finish();
	*/

	cl_int const error_code =
		clReleaseCommandQueue(
			queue_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCommandQueueRelease"));
}
