/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/window/object_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <awl/backends/windows/system/event/handle.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

DWORD const coop_level{
	DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
};

DWORD const buffer_size{
	1024
};

DIPROPDWORD const buffer_settings = {
	{
		fcppt::cast::size<
			DWORD
		>(
			sizeof(DIPROPDWORD)
		),
		fcppt::cast::size<
			DWORD
		>(
			sizeof(DIPROPHEADER)
		),
		0,
		DIPH_DEVICE,
	},
	buffer_size
};

}

sge::dinput::device::object::~object()
{
}

awl::event::container
sge::dinput::device::object::dispatch()
{
	typedef
	std::array<
		DIDEVICEOBJECTDATA,
		buffer_size
	>
	input_buffer;

	input_buffer buffer;

	DWORD elements(
		buffer_size
	);

	awl::event::container events;

	// TODO: Make a range for this
	for(
		;;
	)
	{
		HRESULT const result(
			device_->GetDeviceData(
				fcppt::cast::size<
					DWORD
				>(
					sizeof(
						DIDEVICEOBJECTDATA
					)
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
				DWORD const index
				:
				fcppt::make_int_range_count(
					elements
				)
			)
				fcppt::optional::maybe_void(
					this->on_dispatch(
						buffer[
							index
						]
					),
					[
						&events
					](
						awl::event::base_unique_ptr &&_event
					)
					{
						events.push_back(
							std::move(
								_event
							)
						);
					}
				);
		}

		auto const do_continue(
			[
				this,
				result
			]{
				switch(
					result
				)
				{
				case DI_OK:
					return
						false;
				case DI_BUFFEROVERFLOW:
					return
						true;
				case DIERR_INPUTLOST:
					return
						this->acquire_impl();
				case DIERR_NOTACQUIRED:
					this->acquire_impl();

					return
						false;
				}

				throw
					sge::input::exception{
						FCPPT_TEXT("GetDeviceData() failed!")
					};
			}
		);

		if(
			!do_continue()
		)
			break;
	}

	return
		events;
}

void
sge::dinput::device::object::acquire()
{
	this->acquire_impl();
}

void
sge::dinput::device::object::unacquire()
{
	sge::dinput::device::funcs::unacquire(
		this->get()
	);
}

sge::dinput::device::object::object(
	sge::dinput::device::parameters const &_parameters,
	DIDATAFORMAT const &_format
)
:
	window_{
		_parameters.sge_window()
	},
	device_{
		sge::dinput::create_device(
			_parameters.instance(),
			_parameters.guid()
		)
	}
{
	sge::dinput::device::funcs::set_cooperative_level(
		this->get(),
		_parameters.window(),
		coop_level
	);

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
	this->set_property(
		DIPROP_BUFFERSIZE,
		&buffer_settings.diph
	);
FCPPT_PP_POP_WARNING

	this->set_event_handle(
		_parameters.event_handle().get()
	);

	this->set_data_format(
		_format
	);
}

IDirectInputDevice8 &
sge::dinput::device::object::get()
{
	return
		*device_;
}

sge::window::object &
sge::dinput::device::object::sge_window() const
{
	return
		window_;
}

bool
sge::dinput::device::object::acquire_impl()
{
	return
		sge::dinput::device::funcs::acquire(
			this->get()
		);
}

void
sge::dinput::device::object::set_data_format(
	DIDATAFORMAT const &_format
)
{
	sge::dinput::device::funcs::set_data_format(
		this->get(),
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
		throw
			sge::input::exception{
				FCPPT_TEXT("SetProperty() failed!")
			};
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
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
	case DI_POLLEDDEVICE:
FCPPT_PP_POP_WARNING
		return;
	default:
		throw
			sge::input::exception{
				FCPPT_TEXT("SetEventNotification() failed!")
			};
	}
}
