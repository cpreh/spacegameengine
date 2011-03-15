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


#include "../device.hpp"
#include "../device_parameters.hpp"
#include "../di.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/windows/system/event/handle.hpp>
#include <awl/backends/windows/window/instance.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

namespace
{

DWORD const coop_level(
	DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
);

DIPROPDWORD const buffer_settings = {
	{
		sizeof(DIPROPDWORD),
		sizeof(DIPROPHEADER),
		0,
		DIPH_DEVICE,
	},
	sge::dinput::device::buffer_size
};

}

sge::dinput::device::~device()
{
}

bool
sge::dinput::device::acquire()
{
	switch(
		device_->Acquire()
	)
	{
	case S_FALSE:
	case DI_OK:
		return true;
	case DIERR_OTHERAPPHASPRIO:
		return false;
	default:
		throw sge::input::exception(
			FCPPT_TEXT("Acquire() failed!")
		);
	}
}

void
sge::dinput::device::unacquire()
{
	if(
		device_->Unacquire()
		!= S_FALSE
	)
		throw sge::input::exception(
			FCPPT_TEXT("Unaquire() failed!")
		);
}

sge::dinput::device::device(
	dinput::device_parameters const &_param
)
:
	name_(_param.name()),
	device_()
{
	IDirectInputDevice8 *ret;
	
	if(
		_param.instance()->CreateDevice(
			_param.guid(),
			&ret,
			0
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("dinput: cannot create input device!")
		);

	device_.reset(
		ret
	);

	this->set_cooperative_level(
		_param.window().hwnd(),
		coop_level
	);

	this->set_property(
		DIPROP_BUFFERSIZE,
		&buffer_settings.diph
	);

	this->set_event_handle(
		_param.event_handle().get()
	);
}

void
sge::dinput::device::set_cooperative_level(
	HWND const _hwnd,
	DWORD const _flags
)
{
	if(
		device_->SetCooperativeLevel(
			_hwnd,
			_flags
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("SetCooperativeLevel() failed!")
		);
}

void
sge::dinput::device::set_data_format(
	LPCDIDATAFORMAT const _df
)
{
	if(
		device_->SetDataFormat(
			_df
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("SetDataFormat() failed!")
		);
}

void
sge::dinput::device::set_property(
	REFGUID _guid,
	LPCDIPROPHEADER _diph
)
{
	if(
		device_->SetProperty(
			_guid,
			_diph
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("SetProperty() failed!")
		);
}

void
sge::dinput::device::set_event_handle(
	HANDLE const _handle
)
{
	switch(
		device_->SetEventNotification(
			_handle
		)
	)
	{
	case DI_OK:
	case DI_POLLEDDEVICE:
		return;
	default:
		throw sge::input::exception(
			FCPPT_TEXT("SetEventNotification() failed!")
		);
	}
}

void
sge::dinput::device::poll()
{
	if(
		device_->Poll()
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("Poll() failed!")
		);
}

bool
sge::dinput::device::get_input(
	input_buffer &_data,
	DWORD &_elements
)
{
	_elements = static_cast<DWORD>(_data.size());

	HRESULT const result(
		device_->GetDeviceData(
			sizeof(DIDEVICEOBJECTDATA),
			_data.data(),
			&_elements,
			0
		)
	);

	switch(
		result
	)
	{
	case DI_OK:
	case DI_BUFFEROVERFLOW:
		return true;
	case DIERR_INPUTLOST:
		if(
			!this->acquire()
		)
			return false;

		return
			this->get_input(
				_data,
				_elements
			);
	case DIERR_NOTACQUIRED:
		this->acquire();

		return false;
	default:
		throw sge::input::exception(
			FCPPT_TEXT("GetDeviceData() failed!")
		);
	}
}

void
sge::dinput::device::enum_objects(
	LPDIENUMDEVICEOBJECTSCALLBACK const _fun
)
{
	if(
		device_->EnumObjects(
			_fun,
			this,
			DIDFT_ALL
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("enumerating objects failed!")
		);
}

fcppt::string const &
sge::dinput::device::name() const
{
	return name_;
}


#ifndef _MSC_VER
std::size_t const sge::dinput::device::buffer_size;
#endif
