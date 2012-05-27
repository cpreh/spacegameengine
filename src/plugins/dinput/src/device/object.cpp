/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/dinput/create_device.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters.hpp>
#include <sge/dinput/device/funcs/acquire.hpp>
#include <sge/dinput/device/funcs/set_cooperative_level.hpp>
#include <sge/dinput/device/funcs/set_data_format.hpp>
#include <sge/dinput/device/funcs/unacquire.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/windows/system/event/handle.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array_impl.hpp>


namespace
{

DWORD const coop_level(
	DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
);

DWORD const buffer_size(
	1024
);

DIPROPDWORD const buffer_settings = {
	{
		sizeof(DIPROPDWORD),
		sizeof(DIPROPHEADER),
		0,
		DIPH_DEVICE,
	},
	buffer_size
};

}

sge::dinput::device::object::~object()
{
}

void
sge::dinput::device::object::dispatch()
{
	typedef fcppt::container::array<
		DIDEVICEOBJECTDATA,
		buffer_size
	> input_buffer;

	input_buffer buffer;

	DWORD elements(
		buffer_size
	);

	for(
		;;
	)
	{
		HRESULT const result(
			device_->GetDeviceData(
				sizeof(
					DIDEVICEOBJECTDATA
				),
				buffer.data(),
				&elements,
				0u
			)
		);

		if(
			result == DI_OK
			||
			result == DI_BUFFEROVERFLOW
		)
		{
			for(
				DWORD index(
					0u
				);
				index < elements;
				++index
			)
				this->on_dispatch(
					buffer[
						index
					]
				);
		}

		switch(
			result
		)
		{
		case DI_OK:
			return;
		case DI_BUFFEROVERFLOW:
			break;
		case DIERR_INPUTLOST:
			if(
				!this->acquire()
			)
				return;

			break;
		case DIERR_NOTACQUIRED:
			this->acquire();

			return;
		default:
			throw sge::input::exception(
				FCPPT_TEXT("GetDeviceData() failed!")
			);
		}
	}
}

bool
sge::dinput::device::object::acquire()
{
	return
		sge::dinput::device::funcs::acquire(
			device_.get()
		);
}

void
sge::dinput::device::object::unacquire()
{
	sge::dinput::device::funcs::unacquire(
		device_.get()
	);
}

sge::dinput::device::object::object(
	dinput::device::parameters const &_param
)
:
	device_(
		sge::dinput::create_device(
			_param.instance(),
			_param.guid()
		)
	)
{
	sge::dinput::device::funcs::set_cooperative_level(
		device_.get(),
		_param.window(),
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
sge::dinput::device::object::set_data_format(
	LPCDIDATAFORMAT const _format
)
{
	sge::dinput::device::funcs::set_data_format(
		device_.get(),
		_format
	);
}

void
sge::dinput::device::object::set_property(
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
sge::dinput::device::object::set_event_handle(
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

IDirectInputDevice8 &
sge::dinput::device::object::get()
{
	return
		*device_;
}
