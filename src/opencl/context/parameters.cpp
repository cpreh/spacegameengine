#include <sge/opencl/context/parameters.hpp>

sge::opencl::context::parameters::parameters(
	platform::object &_platform,
	device::object_ref_sequence const &_device_refs)
:
	platform_(
		_platform),
	device_refs_(
		_device_refs),
	error_callback_(),
	shared_renderer_(0)
{
}

sge::opencl::context::parameters &
sge::opencl::context::parameters::error_callback(
	opencl::context::error_callback const &_error_callback)
{
	error_callback_ =
		_error_callback;
	return *this;
}

sge::opencl::context::parameters &
sge::opencl::context::parameters::share_with(
	renderer::device &_shared_renderer)
{
	shared_renderer_ =
		&_shared_renderer;
	return *this;
}

sge::opencl::device::object_ref_sequence const &
sge::opencl::context::parameters::device_refs() const
{
	return device_refs_;
}

sge::opencl::context::error_callback const &
sge::opencl::context::parameters::error_callback() const
{
	return error_callback_;
}

sge::renderer::device *
sge::opencl::context::parameters::shared_renderer() const
{
	return shared_renderer_;
}

sge::opencl::platform::object &
sge::opencl::context::parameters::platform() const
{
	return platform_;
}
