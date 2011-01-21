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
#include "../cursor.hpp"
#include "../device_parameters.hpp"
#include "../device.hpp"
#include "../di.hpp"
#include "../keyboard.hpp"
#include "../mouse.hpp"
#include <sge/input/exception.hpp>
#include <sge/window/instance.hpp>
#include <awl/backends/windows/system/event/object.hpp>
#include <awl/backends/windows/system/event/processor.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/backends/windows/window/instance.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

sge::dinput::processor::processor(
	dinput::dinput_ptr const _dinput,
	sge::window::instance_ptr const _window
)
:
	dinput_(_dinput),
	window_(_window),
	windows_window_(
		fcppt::dynamic_pointer_cast<
			awl::backends::windows::window::instance
		>(
			_window->awl_instance()
		)
	),
	event_processor_(
		fcppt::dynamic_pointer_cast<
			awl::backends::windows::window::event::processor
		>(
			_window->awl_window_event_processor()
		)
	),
	system_processor_(
		fcppt::dynamic_pointer_cast<
			awl::backends::windows::system::event::processor
		>(
			_window->awl_system_event_processor()
		)
	),
	keyboards_(),
	mice_(),
	cursor_(
		fcppt::make_shared_ptr<
			dinput::cursor
		>(
			event_processor_
		)
	),
	key_conv_(),
	poll_timer_(
		USER_TIMER_MINIMUM
	),
	acquired_(false),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				event_processor_->register_callback(
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
				system_processor_->register_callback(
					WM_TIMER,
					std::tr1::bind(
						&dinput::processor::on_timer,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
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
sge::dinput::processor::on_timer(
	awl::backends::windows::system::event::object const &_event
)
{
	if(
		_event.wparam() != poll_timer_.id()
	)
		return;
	
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

	dinput::device_parameters const parameters(
		instance.dinput_,
		product_name,
		_ddi->guidInstance,
		instance.windows_window_
	);
	
	switch(
		dev_type
	)
	{
	case DI8DEVTYPE_KEYBOARD:
		instance.keyboards_.push_back(
			fcppt::make_shared_ptr<
				dinput::keyboard
			>(
				parameters,
				instance.key_conv_
			)
		);
		break;
	case DI8DEVTYPE_MOUSE:
		instance.mice_.push_back(
			fcppt::make_shared_ptr<
				dinput::mouse
			>(
				parameters
			)
		);
		break;
	/*
	case DI8DEVTYPE_JOYSTICK:
		SetDataFormat(Device,&c_dfDIJoystick2);

		DIPROPRANGE	Range;
		Range.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
		Range.diph.dwSize		= sizeof(DIPROPRANGE);
		Range.diph.dwObj		= 0;
		Range.diph.dwHow		= DIPH_DEVICE;
		Range.lMin				= -1000;
		Range.lMax				= +1000;
		SetProperty(Device,DIPROP_RANGE,&Range.diph);

		DIPROPDWORD	DeadZone;
		DeadZone.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
		DeadZone.diph.dwSize		= sizeof(DIPROPDWORD);
		DeadZone.diph.dwObj			= 0;
		DeadZone.diph.dwHow			= DIPH_DEVICE;
		DeadZone.dwData				= 1000;
		SetProperty(Device,DIPROP_DEADZONE,&DeadZone.diph);

		DIPROPDWORD	Saturation;
		Saturation.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
		Saturation.diph.dwSize			= sizeof(DIPROPDWORD);
		Saturation.diph.dwObj			= 0;
		Saturation.diph.dwHow			= DIPH_DEVICE;
		Saturation.dwData				= 9000;
		SetProperty(Device,DIPROP_SATURATION,&Saturation.diph);

		++sys->joysticks;*/
	}
	return DIENUM_CONTINUE;
}
