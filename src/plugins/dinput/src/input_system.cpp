/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <stdexcept>
#include "../input_system.hpp"
#include "../keyboard.hpp"
#include "../mouse.hpp"
#include "../../../win32_window.hpp"
#include "../../../win32_conv.hpp"

sge::dinput::input_system::input_system(const win32_window_ptr wnd)
 : wnd(wnd)
{
	direct_input* d;
	if(DirectInput8Create(GetModuleHandle(0),
	                      DIRECTINPUT_VERSION,
	                      IID_IDirectInput8A,
	                      reinterpret_cast<LPVOID*>(&d),
	                      0) != DI_OK)
		throw std::runtime_error("Cannot create direct input");
	di.reset(d);

	if(di->EnumDevices(DI8DEVCLASS_ALL,
	                   di_enum_devices_callback,
	                   this,
	                   DIEDFL_ATTACHEDONLY) != DI_OK)
		throw std::runtime_error("DirectInput Enumeration failed");
}

boost::signals::connection sge::dinput::input_system::register_callback(const callback& c)
{
	return sig.connect(c);
}

boost::signals::connection sge::dinput::input_system::register_repeat_callback(const repeat_callback& c)
{
	return repeat_sig.connect(c);
}

void sge::dinput::input_system::dispatch()
{
	for(device_array::iterator it = devices.begin(); it != devices.end(); ++it)
		it->dispatch(sig);
	// FIXME: dispatch repeated signals as well
}

BOOL sge::dinput::input_system::di_enum_devices_callback(LPCDIDEVICEINSTANCE ddi, LPVOID s)
{
	input_system& sys = *static_cast<input_system*>(s);
	const unsigned char dev_type = static_cast<unsigned char>(ddi->dwDevType & 0xFF);

	const string product_name = win_str_to_sge(ddi->tszProductName);

	switch(dev_type) {
	case DI8DEVTYPE_KEYBOARD:
		sys.devices.push_back(new keyboard(sys.di, product_name, ddi->guidInstance, sys.wnd->hwnd(), sys.key_conv));
		break;
	case DI8DEVTYPE_MOUSE:
		sys.devices.push_back(new mouse(sys.di, product_name, ddi->guidInstance, sys.wnd->hwnd()));
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
