//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/command_queue/execution_mode.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/command_queue/profiling_mode.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <fcppt/text.hpp>


sge::opencl::command_queue::object::object(
	opencl::device::object &_device,
	opencl::context::object &_context,
	command_queue::execution_mode const execution_mode,
	command_queue::profiling_mode const profiling_mode)
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

	opencl::impl::handle_error(
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

	opencl::impl::handle_error(
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

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clCommandQueueRelease"));
}
