/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../keyboard.hpp"
#include "../mouse.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/windows/window.hpp>
#include <boost/foreach.hpp>

sge::dinput::system::system(
	windows::window_ptr const wnd)
:
	wnd(wnd)
{
	direct_input* d;
	if(DirectInput8Create(
		GetModuleHandle(0),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8A,
		reinterpret_cast<LPVOID*>(&d), // this is undefined but Direct Input wants us to do it
		0)
	!= DI_OK)
		throw exception(
			SGE_TEXT("Cannot create direct input!"));
	di.reset(d);

	if(di->EnumDevices(
		DI8DEVCLASS_ALL,
		di_enum_devices_callback,
		this,
		 DIEDFL_ATTACHEDONLY)
	!= DI_OK)
		throw exception(
			SGE_TEXT("DirectInput Enumeration failed!"));
}

sge::signal::auto_connection
sge::dinput::system::register_callback(
	input::callback const &c)
{
	return sig.connect(c);
}

sge::signal::auto_connection
sge::dinput::system::register_repeat_callback(
	input::repeat_callback const &c)
{
	return repeat_sig.connect(c);
}

void sge::dinput::system::dispatch()
{
	BOOST_FOREACH(device_array::reference r, devices)
		r.dispatch(sig);
	// FIXME: dispatch repeated signals as well
}

BOOL sge::dinput::system::di_enum_devices_callback(
	LPCDIDEVICEINSTANCE ddi,
	LPVOID s)
{
	system &sys = *static_cast<system*>(s);

	unsigned char const dev_type
		= static_cast<unsigned char>(
			ddi->dwDevType & 0xFF);

	string const product_name
		= ddi->tszProductName;

	switch(dev_type) {
	case DI8DEVTYPE_KEYBOARD:
		sys.devices.push_back(
			new keyboard(
				sys.di,
				product_name,
				ddi->guidInstance,
				sys.wnd,
				sys.key_conv,
				sys.repeat_sig
			)
		);
		break;
	case DI8DEVTYPE_MOUSE:
		sys.devices.push_back(
			new mouse(
				sys.di,
				product_name,
				ddi->guidInstance,
				sys.wnd
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

sge::window::instance_ptr const
sge::dinput::system::window() const
{
	return sge::static_pointer_cast<
		sge::window::instance
	>(wnd);
}
