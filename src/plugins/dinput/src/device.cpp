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


#include "../device.hpp"
#include <sge/windows/window.hpp>
#include <sge/optional_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

namespace
{

DWORD const coop_level(
	DISCL_FOREGROUND | DISCL_EXCLUSIVE);

DIPROPDWORD const buffer_settings = {
	{
		sizeof(DIPROPDWORD),
		sizeof(DIPROPHEADER),
		0,
		DIPH_DEVICE,
	},
	sge::dinput::device::buffer_size
};

class activate_handler {
public:
	typedef sge::windows::callback_return_type result_type;

	explicit activate_handler(
		sge::dinput::device &);

	result_type const
	operator()(
		sge::windows::window &,
		sge::windows::event_type,
		WPARAM,
		LPARAM) const;
private:
	sge::dinput::device &device;
};

}

sge::dinput::device::~device()
{}

void sge::dinput::device::acquire()
{
	switch(device_->Acquire()) {
	case S_FALSE:
	case DI_OK:
		return;
	case DIERR_OTHERAPPHASPRIO:
		break;
	default:
		throw exception(
			FCPPT_TEXT("Acquire() failed!"));
	}
}

void sge::dinput::device::unacquire()
{
	if(device_->Unacquire() != S_FALSE)
		throw exception(
			FCPPT_TEXT("Unaquire() failed!")
		);
}

sge::dinput::device::device(
	dinput_ptr const di,
	string const &name_,
	GUID const guid,
	windows::window_ptr const window)
:
	name_(name_),
	activate_connection(
		window->register_callback(
			WM_ACTIVATE,
			activate_handler(
				*this
			)
		)
	),
	device_()
{
	direct_input_device* d;
	if(di->CreateDevice(guid, &d, 0) != DI_OK)
		throw exception(
			FCPPT_TEXT("dinput: cannot create input device!"));
	device_.reset(d);
	set_cooperative_level(window->hwnd(),coop_level);
	set_property(DIPROP_BUFFERSIZE, &buffer_settings.diph);
}

void sge::dinput::device::set_cooperative_level(
	HWND const hwnd,
	DWORD const flags)
{
	if(device_->SetCooperativeLevel(hwnd, flags) != DI_OK)
		throw exception(
			FCPPT_TEXT("SetCooperativeLevel() failed!"));
}

void sge::dinput::device::set_data_format(
	LPCDIDATAFORMAT const df)
{
	if(device_->SetDataFormat(df) != DI_OK)
		throw exception(
			FCPPT_TEXT("SetDataFormat() failed!"));
}

void sge::dinput::device::set_property(
	REFGUID guid,
	LPCDIPROPHEADER diph)
{
	if(device_->SetProperty(guid, diph) != DI_OK)
		throw exception(
			FCPPT_TEXT("SetProperty() failed!"));
}

void sge::dinput::device::poll()
{
	if(device_->Poll() != DI_OK)
		throw exception(FCPPT_TEXT("Poll() failed!"));
}

bool sge::dinput::device::get_input(
	input_buffer &data,
	DWORD &elements,
	unsigned const d)
{
	elements = static_cast<DWORD>(data.size());
	HRESULT const res = device_->GetDeviceData(
		sizeof(DIDEVICEOBJECTDATA),
		data.data(),
		&elements,
		0);

	switch(res) {
	case DI_OK:
	case DI_BUFFEROVERFLOW:
		return true;
	case DIERR_INPUTLOST:
		acquire();
		return get_input(
			data,
			elements,
			d + 1);
	case DIERR_NOTACQUIRED:
		acquire();
		return false;
	default:
		throw exception(
			FCPPT_TEXT("GetDeviceData() failed!"));
	}
}

void sge::dinput::device::enum_objects(
	LPDIENUMDEVICEOBJECTSCALLBACK const fun)
{
	if(device_->EnumObjects(fun, this, DIDFT_ALL) != DI_OK)
		throw exception(
			FCPPT_TEXT("enumerating objects failed!"));
}

sge::string const &
sge::dinput::device::name() const
{
	return name_;
}


#ifndef _MSC_VER
std::size_t const sge::dinput::device::buffer_size;
#endif

namespace
{

activate_handler::activate_handler(
	sge::dinput::device &device)
:
	device(device)
{}

activate_handler::result_type const
activate_handler::operator()(
	sge::windows::window &,
	sge::windows::event_type,
	WPARAM const wparam,
	LPARAM) const
{
	bool const active = wparam != 0 ? true : false;
	if(active)
		device.acquire();
	else
		device.unacquire();

	return sge::windows::callback_return_type();
}

}
