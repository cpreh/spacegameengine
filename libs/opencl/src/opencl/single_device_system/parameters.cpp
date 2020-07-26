//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/single_device_system/parameters.hpp>


sge::opencl::single_device_system::parameters::parameters()
:
	renderer_(),
	error_callback_(),
	profiling_(
		sge::opencl::command_queue::profiling_mode::disabled),
	execution_mode_(
		sge::opencl::command_queue::execution_mode::in_order),
	prefers_gpu_(
		false)
{
}

sge::opencl::single_device_system::parameters &
sge::opencl::single_device_system::parameters::renderer(
	sge::renderer::device::core_ref const _renderer
)
{
	renderer_ =
		sge::opencl::single_device_system::optional_renderer(
			_renderer
		);

	return *this;
}

sge::opencl::single_device_system::parameters &
sge::opencl::single_device_system::parameters::enable_profiling()
{
	profiling_ = command_queue::profiling_mode::enabled;
	return *this;
}

sge::opencl::single_device_system::parameters &
sge::opencl::single_device_system::parameters::context_error_callback(
	opencl::context::error_callback const &_error_callback)
{
	error_callback_ =
		opencl::context::optional_error_callback(
			_error_callback);
	return *this;
}

sge::opencl::single_device_system::parameters &
sge::opencl::single_device_system::parameters::prefer_gpu(
	bool const _prefers_gpu)
{
	prefers_gpu_ =
		_prefers_gpu;
	return *this;
}

sge::opencl::single_device_system::parameters &
sge::opencl::single_device_system::parameters::execution_mode(
	sge::opencl::command_queue::execution_mode const _execution_mode)
{
	execution_mode_ =
		_execution_mode;
	return *this;
}

sge::opencl::single_device_system::optional_renderer const &
sge::opencl::single_device_system::parameters::renderer() const
{
	return
		renderer_;
}

sge::opencl::context::optional_error_callback const &
sge::opencl::single_device_system::parameters::error_callback() const
{
	return error_callback_;
}

sge::opencl::command_queue::profiling_mode
sge::opencl::single_device_system::parameters::profiling() const
{
	return profiling_;
}

sge::opencl::command_queue::execution_mode
sge::opencl::single_device_system::parameters::execution_mode() const
{
	return execution_mode_;
}

bool
sge::opencl::single_device_system::parameters::prefers_gpu() const
{
	return prefers_gpu_;
}
