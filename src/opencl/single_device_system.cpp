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


#include <sge/exception.hpp>
#include <sge/opencl/single_device_system.hpp>
#include <sge/opencl/system.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/src/opencl/declare_local_logger.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/thread/locks.hpp>
#include <fcppt/config/external_end.hpp>


SGE_OPENCL_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("single_device_system"))

namespace
{
sge::opencl::context::parameters const
construct_context_parameters(
	sge::opencl::platform::object &_platform,
	sge::opencl::device::object &_device,
	sge::opencl::context::error_callback const &_error_callback,
	sge::opencl::optional_renderer const &_renderer)
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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::opencl::single_device_system::single_device_system(
	opencl::optional_renderer const &_renderer,
	opencl::context::optional_error_callback const &_error_callback)
:
	system_(
		fcppt::make_unique_ptr<sge::opencl::system>()),
	platform_(
		&system_->platforms().front()),
	device_(
		&platform_->devices().front()),
	context_(
		fcppt::make_unique_ptr<context::object>(
			::construct_context_parameters(
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
			command_queue::profiling_mode::disabled)),
	error_mutex_(),
	error_occured_(
		false),
	error_information_(),
	error_data_(),
	error_callback_(
		_error_callback)
{
}
FCPPT_PP_POP_WARNING

SGE_OPENCL_SYMBOL void
sge::opencl::single_device_system::update()
{
	boost::lock_guard<boost::mutex> l(
		error_mutex_);

	if(!error_occured_)
		return;

	if(!error_callback_)
		throw
			sge::exception(
				FCPPT_TEXT("An asynchronous error occured: ")+
				fcppt::from_std_string(
					error_information_));

	(*error_callback_)(
		error_information_,
		error_data_);
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
sge::opencl::single_device_system::command_queue()
{
	return *queue_;
}

sge::opencl::command_queue::object const &
sge::opencl::single_device_system::command_queue() const
{
	return *queue_;
}

sge::opencl::single_device_system::~single_device_system()
{
}

void
sge::opencl::single_device_system::error_callback(
	opencl::error_information_string const &_error_information,
	opencl::binary_error_data const &_error_data)
{
	boost::lock_guard<boost::mutex> l(
		error_mutex_);

	error_information_ =
		_error_information;

	error_data_ =
		_error_data;

	FCPPT_LOG_ERROR(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("An error in a context occured: \"")
			<<
				fcppt::from_std_string(
					_error_information)
			<< FCPPT_TEXT("\""));
}
