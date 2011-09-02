#include <sge/opencl/program/build_parameters.hpp>

sge::opencl::program::build_parameters::build_parameters()
:
	devices_(),
	build_options_(),
	notification_callback_()
{
}

sge::opencl::program::build_parameters &
sge::opencl::program::build_parameters::devices(
	device::object_ref_sequence const &_devices)
{
	devices_ =
		_devices;
	return *this;
}

sge::opencl::program::build_parameters &
sge::opencl::program::build_parameters::options(
	program::build_options const &_build_options)
{
	build_options_ =
		_build_options;
	return *this;
}

sge::opencl::program::build_parameters &
sge::opencl::program::build_parameters::notification_callback(
	program::notification_callback const &_notification_callback)
{
	notification_callback_ =
		_notification_callback;
	return *this;
}

fcppt::optional<sge::opencl::device::object_ref_sequence> const &
sge::opencl::program::build_parameters::devices() const
{
	return devices_;
}

sge::opencl::program::build_options const &
sge::opencl::program::build_parameters::build_options() const
{
	return build_options_;
}

sge::opencl::program::notification_callback const &
sge::opencl::program::build_parameters::notification_callback() const
{
	return notification_callback_;
}
