/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../system.hpp"
#include "../cursor.hpp"
#include "../di.hpp"
#include "../keyboard.hpp"
#include "../mouse.hpp"
#include <sge/input/exception.hpp>
#include <sge/window/instance.hpp>
#include <awl/backends/windows/window/instance.hpp>
#include <awl/backends/windows/module_handle.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

sge::dinput::processor::processor(
	sge::window::instance_ptr const _window
)
:
	devices_(),
	dinput_(),
	window_(_window),
	windows_window_(
		fcppt::dynamic_pointer_cast<
			awl::backends::windows::window::instance
		>(
			_window->awl_window()
		)
	),
	key_conv_()
{
	IDirectInput8 *instance;

	if(
		::DirectInput8Create(
			awl::backends::windows::module_handle(),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8A,
			reinterpret_cast<LPVOID *>(&instance), // this is undefined but Direct Input wants us to do it
			0
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("Cannot create direct input!")
		);

	dinput_.reset(
		instance
	);

	if(
		dinput_->EnumDevices(
			DI8DEVCLASS_ALL,
			di_enum_devices_callback,
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
sge::dinput::processor:keyboard_discover_callback(
	input::keyboard::discover_callback const &
)
{
}

fcppt::signal::auto_connection
sge::dinput::processor:keyboard_remove_callback(
	input::keyboard::remove_callback const &
)
{
}

sge::input::keyboard::device_vector const
sge::dinput::processor:keyboards() const
{
}

fcppt::signal::auto_connection
sge::dinput::processor:mouse_discover_callback(
	input::mouse::discover_callback const &
)
{
}

fcppt::signal::auto_connection
sge::dinput::processor:mouse_remove_callback(
	input::mouse::remove_callback const &
)
{
}

sge::input::mouse::device_vector const
sge::dinput::processor:mice() const
{
}

fcppt::signal::auto_connection
sge::dinput::processor:cursor_discover_callback(
	input::cursor::discover_callback const &
)
{
}

fcppt::signal::auto_connection
sge::dinput::processor:cursor_remove_callback(
	input::cursor::remove_callback const &
)
{
}

sge::input::cursor::object_vector const
sge::dinput::processor:cursors() const
{
}

sge::window::instance_ptr const
sge::dinput::processor::window() const
{
	return window_;
}

void
sge::dinput::processor::dispatch()
{
	BOOST_FOREACH(
		device_array::reference device,
		devices_
	)
		device.dispatch();
}

BOOL
sge::dinput::processor::di_enum_devices_callback(
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
		fcppt::container::ptr::push_back_unique_ptr(
			instance.devices_,
			fcppt::make_unique_ptr<
				dinput::keyboard
			>(
				parameters,
				instance.key_conv_,
			)
		);
		break;
	case DI8DEVTYPE_MOUSE:
		fcppt::container::ptr::push_back_unique_ptr(
			instance.devices_,
			fcppt::make_unique_ptr<
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
