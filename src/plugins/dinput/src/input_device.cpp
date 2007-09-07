/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../../../exception.hpp"
#include "../../../util.hpp"
#include "../input_device.hpp"

const DWORD sge::dinput::input_device::coop_level(DISCL_FOREGROUND | DISCL_EXCLUSIVE);
const DIPROPDWORD sge::dinput::input_device::buffer_settings = {
	{ sizeof(DIPROPDWORD),
	  sizeof(DIPROPHEADER),
	  0,
	  DIPH_DEVICE,
	},
	buffer_size
};

sge::dinput::input_device::input_device(const dinput_ptr di, const string& _name, const GUID guid, sge::win32_window_ptr window)
: _name(_name)
{
	direct_input_device* d;
	if(di->CreateDevice(guid,&d,0) != DI_OK)
		throw exception("dinput: cannot create input device");
	device.reset(d);
	set_cooperative_level(window->hwnd(),coop_level);
	set_property(DIPROP_BUFFERSIZE,&buffer_settings.diph);

	window->register_callback(WM_ACTIVATE, lost_focus_unacquire_handler(*this));
}

void sge::dinput::input_device::set_cooperative_level(const HWND hwnd, const DWORD flags)
{
	if(device->SetCooperativeLevel(hwnd,flags) != DI_OK)
		throw exception("SetCooperativeLevel() failed");
}

void sge::dinput::input_device::set_data_format(const LPCDIDATAFORMAT df)
{
	if(device->SetDataFormat(df) != DI_OK)
		throw exception("SetDataFormat() failed");
}

void sge::dinput::input_device::set_property(REFGUID guid, LPCDIPROPHEADER diph)
{
	if(device->SetProperty(guid,diph) != DI_OK)
		throw exception("SetProperty() failed");
}

void sge::dinput::input_device::acquire()
{
	switch(device->Acquire()) {
	case S_FALSE:
	case DI_OK:
		return;
	case DIERR_OTHERAPPHASPRIO:
		break;
	default:
		throw exception("Acquire() failed");
	}
}

void sge::dinput::input_device::unacquire()
{
}

void sge::dinput::input_device::poll()
{
	if(device->Poll() != DI_OK)
		throw exception("Poll() failed");
}

bool sge::dinput::input_device::_get_input(input_buffer data, DWORD& elements, unsigned d)
{
	elements = sizeof(input_buffer) / sizeof(DIDEVICEOBJECTDATA);
	const HRESULT res = device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), data, &elements, 0);
	switch(res) {
	case DI_OK:
	case DI_BUFFEROVERFLOW:
		return true;
	case DIERR_INPUTLOST:
		acquire();
		return _get_input(data,elements,d+1);
	case DIERR_NOTACQUIRED:
		acquire();
		return false;
	default:
		throw exception("GetDeviceData() failed");
	}
}

void sge::dinput::input_device::enum_objects(LPDIENUMDEVICEOBJECTSCALLBACK fun)
{
	if(device->EnumObjects(fun,this,DIDFT_ALL) != DI_OK)
		throw exception("enumerating objects failed");
}

const sge::string& sge::dinput::input_device::name() const
{
	return _name;
}

sge::win32_window::win32_callback_return_type sge::dinput::input_device::lost_focus_unacquire_handler::operator()(sge::win32_window&, sge::win32_window::win32_event_type, WPARAM wparam, LPARAM)
{
	const bool active = wparam != 0 ? true : false;
	if(active)
		device.unacquire();
	else
		device.acquire();

	return sge::win32_window::win32_callback_return_type();
}

#ifndef _MSC_VER
const std::size_t sge::dinput::input_device::buffer_size;
#endif
