#include "../handle_error.hpp"
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/command_queue/execution_mode.hpp>
#include <fcppt/text.hpp>

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

sge::opencl::command_queue::object::~object()
{
	cl_int const error_code =
		clReleaseCommandQueue(
			queue_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCommandQueueRelease"));
}
