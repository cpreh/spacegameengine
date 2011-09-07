#include <sge/opencl/single_device_system.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/system.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/assign/make_container.hpp>

namespace
{
sge::opencl::context::parameters const
construct_context_parameters(
	sge::opencl::platform::object &_platform,
	sge::opencl::device::object &_device,
	sge::opencl::context::error_callback const &_error_callback,
	sge::renderer::device *_renderer)
{
	sge::opencl::context::parameters result(
		_platform,
		fcppt::assign::make_container<sge::opencl::device::object_ref_sequence>(
			&_device));

	result.error_callback(
		_error_callback);

	if(_renderer)
		result.share_with(
			*_renderer);

	return result;
}
}

sge::opencl::single_device_system::single_device_system(
	renderer::device *_renderer)
:
	system_(
		fcppt::make_unique_ptr<sge::opencl::system>()),
	platform_(
		&system_->platforms().front()),
	device_(
		&platform_->devices().front()),
	context_(
		fcppt::make_unique_ptr<context::object>(
			construct_context_parameters(
				*platform_,
				*device_,
				std::tr1::bind(
					&single_device_system::error_callback,
					this,
					std::tr1::placeholders::_1,
					std::tr1::placeholders::_2),
				_renderer))),
	queue_(
		fcppt::make_unique_ptr<command_queue::object>(
			fcppt::ref(
				*device_),
			fcppt::ref(
				*context_),
			command_queue::execution_mode::in_order,
			command_queue::profiling_mode::disabled))
{
}

sge::opencl::system &
sge::opencl::single_device_system::system()
{
	return *system_;
}

sge::opencl::system const &
sge::opencl::single_device_system::system() const
{
	return *system_;
}

sge::opencl::platform::object &
sge::opencl::single_device_system::platform()
{
	return *platform_;
}

sge::opencl::platform::object const &
sge::opencl::single_device_system::platform() const
{
	return *platform_;
}

sge::opencl::device::object &
sge::opencl::single_device_system::device()
{
	return *device_;
}

sge::opencl::device::object const &
sge::opencl::single_device_system::device() const
{
	return *device_;
}

sge::opencl::context::object &
sge::opencl::single_device_system::context()
{
	return *context_;
}

sge::opencl::context::object const &
sge::opencl::single_device_system::context() const
{
	return *context_;
}

sge::opencl::command_queue::object &
sge::opencl::single_device_system::queue()
{
	return *queue_;
}

sge::opencl::command_queue::object const &
sge::opencl::single_device_system::queue() const
{
	return *queue_;
}

sge::opencl::single_device_system::~single_device_system()
{
}

void
sge::opencl::single_device_system::error_callback(
	opencl::error_information_string const &err,
	opencl::binary_error_data const &)
{
	throw
		sge::exception(
			FCPPT_TEXT("An error in a context occured: \"")+
			fcppt::from_std_string(
				err)+
			FCPPT_TEXT("\""));
}
