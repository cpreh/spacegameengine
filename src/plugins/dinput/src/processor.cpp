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


#include "../processor.hpp"
#include "../cursor/object.hpp"
#include "../device/parameters.hpp"
#include "../device/object.hpp"
#include "../keyboard/device.hpp"
#include "../mouse/device.hpp"
#include "../create_device.hpp"
#include "../create_dinput.hpp"
#include "../di.hpp"
#include <sge/input/exception.hpp>
#include <sge/window/instance.hpp>
#include <awl/backends/windows/system/event/handle.hpp>
#include <awl/backends/windows/system/event/processor.hpp>
#include <awl/backends/windows/window/instance.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/foreach.hpp>
#include <fcppt/config/external_end.hpp>


sge::dinput::processor::processor(
	sge::window::instance_ptr const _window
)
:
	dinput_(
		dinput::create_dinput()
	),
	window_(_window),
	windows_window_(
		dynamic_cast<
			awl::backends::windows::window::instance &
		>(
			*_window->awl_instance()
		)
	),
	event_processor_(
		dynamic_cast<
			awl::backends::windows::window::event::processor &
		>(
			*_window->awl_window_event_processor()
		)
	),
	system_processor_(
		dynamic_cast<
			awl::backends::windows::system::event::processor &
		>(
			*_window->awl_system_event_processor()
		)
	),
	keyboards_(),
	mice_(),
	system_mouse_(
		dinput::create_device(
			dinput_.get(),
			GUID_SysMouse
		)
	),
	cursor_(
		fcppt::make_shared_ptr<
			dinput::cursor::object
		>(
			fcppt::ref(
				event_processor_
			),
			fcppt::ref(
				windows_window_
			),
			system_mouse_.get()
		)
	),
	event_handle_(
		system_processor_.create_event_handle()
	),
	key_conv_(),
	acquired_(false),
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				event_processor_.register_callback(
					WM_ACTIVATE,
					std::tr1::bind(
						&dinput::processor::on_activate,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				system_processor_.register_handle_callback(
					std::tr1::bind(
						&dinput::processor::on_handle_ready,
						this
					)
				)
			)
		)
	)
FCPPT_PP_POP_WARNING
{
	if(
		dinput_->EnumDevices(
			DI8DEVCLASS_ALL,
			enum_devices_callback,
			this,
			DIEDFL_ATTACHEDONLY
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("DirectInput Enumeration failed!")
		);
}

sge::dinput::processor::~processor()
{
}

fcppt::signal::auto_connection
sge::dinput::processor::keyboard_discover_callback(
	input::keyboard::discover_callback const &
)
{
	return fcppt::signal::auto_connection();
}

fcppt::signal::auto_connection
sge::dinput::processor::keyboard_remove_callback(
	input::keyboard::remove_callback const &
)
{
	return fcppt::signal::auto_connection();
}

sge::input::keyboard::device_vector const
sge::dinput::processor::keyboards() const
{
	return
		sge::input::keyboard::device_vector(
			keyboards_.begin(),
			keyboards_.end()
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::mouse_discover_callback(
	input::mouse::discover_callback const &
)
{
	return fcppt::signal::auto_connection();
}

fcppt::signal::auto_connection
sge::dinput::processor::mouse_remove_callback(
	input::mouse::remove_callback const &
)
{
	return fcppt::signal::auto_connection();
}

sge::input::mouse::device_vector const
sge::dinput::processor::mice() const
{
	return
		sge::input::mouse::device_vector(
			mice_.begin(),
			mice_.end()
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::cursor_discover_callback(
	input::cursor::discover_callback const &
)
{
	return fcppt::signal::auto_connection();
}

fcppt::signal::auto_connection
sge::dinput::processor::cursor_remove_callback(
	input::cursor::remove_callback const &
)
{
	return fcppt::signal::auto_connection();
}

sge::input::cursor::object_vector const
sge::dinput::processor::cursors() const
{
	return
		sge::input::cursor::object_vector(
			1u,
			cursor_
		);
}

fcppt::signal::auto_connection
sge::dinput::processor::joypad_discover_callback(
	input::joypad::discover_callback const &
)
{
	return fcppt::signal::auto_connection();
}

fcppt::signal::auto_connection
sge::dinput::processor::joypad_remove_callback(
	input::joypad::remove_callback const &
)
{
	return fcppt::signal::auto_connection();
}

sge::input::joypad::device_vector const
sge::dinput::processor::joypads() const
{
	return
		sge::input::joypad::device_vector();
}

sge::window::instance_ptr const
sge::dinput::processor::window() const
{
	return window_;
}

awl::backends::windows::window::event::return_type
sge::dinput::processor::on_activate(
	awl::backends::windows::window::event::object const &_event
)
{
	acquired_ = (_event.wparam() != 0);

	if(
		acquired_
	)
	{
		BOOST_FOREACH(
			device_vector::value_type device,
			this->all_devices()
		)
			device->acquire();

		cursor_->acquire();
	}
	else
	{
		BOOST_FOREACH(
			device_vector::value_type device,
			this->all_devices()
		)
			device->unacquire();

		cursor_->unacquire();
	}

	return awl::backends::windows::window::event::return_type();
}

void
sge::dinput::processor::on_handle_ready()
{
	if(
		!acquired_
	)
		return;

	BOOST_FOREACH(
		device_vector::value_type device,
		this->all_devices()
	)
		device->dispatch();
}

sge::dinput::processor::device_vector const
sge::dinput::processor::all_devices() const
{
	// TODO: this should be optimized with iterator ranges

	device_vector ret(
		keyboards_.begin(),
		keyboards_.end()
	);

	fcppt::algorithm::append(
		ret,
		device_vector(
			mice_.begin(),
			mice_.end()
		)
	);

	return ret;
}

BOOL
sge::dinput::processor::enum_devices_callback(
	LPCDIDEVICEINSTANCE _ddi,
	LPVOID _state
)
{
	dinput::processor &instance(
		*static_cast<
			dinput::processor *
		>(
			_state
		)
	);

	DWORD const dev_type(
		_ddi->dwDevType
		& 0xFF
	);

	fcppt::string const product_name(
		_ddi->tszProductName
	);

	dinput::device::parameters const parameters(
		instance.dinput_.get(),
		product_name,
		_ddi->guidInstance,
		instance.windows_window_,
		*instance.event_handle_
	);

	switch(
		dev_type
	)
	{
	case DI8DEVTYPE_KEYBOARD:
		instance.keyboards_.push_back(
			fcppt::make_shared_ptr<
				dinput::keyboard::device
			>(
				parameters,
				fcppt::cref(
					instance.key_conv_
				)
			)
		);
		break;
	case DI8DEVTYPE_MOUSE:
		instance.mice_.push_back(
			fcppt::make_shared_ptr<
				dinput::mouse::device
			>(
				parameters
			)
		);
		break;
	}

	return DIENUM_CONTINUE;
}
