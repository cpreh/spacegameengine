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


#include "../handle_error.hpp"
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/command_queue/execution_mode.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array.hpp>

sge::opencl::command_queue::object::object(
	opencl::device::object &device,
	opencl::context::object &context,
	command_queue::execution_mode::type const execution_mode,
	command_queue::profiling_mode::type const profiling_mode)
:
	queue_()
{
	cl_int error_code;

	queue_ =
		clCreateCommandQueue(
			context.context_,
			device.device_id_,
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

cl_command_queue
sge::opencl::command_queue::object::impl() const
{
	return queue_;
}

template<std::size_t N>
void
sge::opencl::command_queue::object::enqueue(
	kernel::object &_kernel,
	fcppt::container::array<std::size_t,N> const &global_dim,
	fcppt::container::array<std::size_t,N> const &work_dim)
{
	cl_int const error_code =
		clEnqueueNDRangeKernel(
			queue_,
			_kernel.impl(),
			static_cast<cl_uint>(
				N),
			0, // global work offset (not implemented in 1.1)
			global_dim.data(),
			work_dim.data(),
			0,
			0,
			0);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueNDRangeKernel"));
}

template void sge::opencl::command_queue::object::enqueue<1>(
	kernel::object &,
	fcppt::container::array<std::size_t,1> const &,
	fcppt::container::array<std::size_t,1> const &);

template void sge::opencl::command_queue::object::enqueue<2>(
	kernel::object &,
	fcppt::container::array<std::size_t,2> const &,
	fcppt::container::array<std::size_t,2> const &);

template void sge::opencl::command_queue::object::enqueue<3>(
	kernel::object &,
	fcppt::container::array<std::size_t,3> const &,
	fcppt::container::array<std::size_t,3> const &);

sge::opencl::command_queue::object::~object()
{
	cl_int const error_code =
		clReleaseCommandQueue(
			queue_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCommandQueueRelease"));
}
