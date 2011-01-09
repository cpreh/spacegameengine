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


#include "../mouse.hpp"
#include "../di.hpp"
#include "../is_mouse_axis.hpp"
#include "../mouse_axis_code.hpp"
#include "../mouse_button_code.hpp"
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <fcppt/signal/object_impl.hpp>

sge::dinput::mouse::mouse(
	dinput::device_parameters const &_param
)
:
	sge::input::mouse::device(),
	dinput::device(
		_param
	),
	axis_signal_(),
	button_signal_(),
	axis_(),
	buttons_()
{
	this->set_data_format(
		&c_dfDIMouse2
	);

	this->enum_objects(
		enum_mouse_keys
	);

	this->acquire();
}

sge::dinput::mouse::~mouse()
{
}

fcppt::signal::auto_connection
sge::dinput::mouse::button_callback(
	input::mouse::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::mouse::axis_callback(
	input::mouse::axis_callback const &_callback
)
{
	return
		axis_signal_.connect(
			_callback
		);
}

void
sge::dinput::mouse::dispatch()
{
	input_buffer data;

	DWORD elements;

	if(
		!this->get_input(
			data,
			elements
		)
	)
		return;

	for(
		DWORD index = 0;
		index < elements;
		++index
	)
	{
		DWORD const
			offset(
				data[
					index
				].dwOfs
			),
			data_word(
				data[
					index
				].dwData
			);

		if(
			dinput::is_mouse_axis(
				offset
			)
		)
			axis_signal_(
				input::mouse::axis_event(
					axis_[
						offset
					],
					static_cast<
						sge::input::mouse::axis_value
					>(
						data_word
					)
				)
			);
		else
			button_signal_(
				input::mouse::button_event(
					buttons_[
						offset
					],
					(
						data_word
						& 0x80
					)
					!= 0
				)
			);
	}
}

BOOL
sge::dinput::mouse::enum_mouse_keys(
	LPCDIDEVICEOBJECTINSTANCE _ddoi,
	LPVOID _state
)
{
	dinput::mouse &instance(
		*static_cast<
			dinput::mouse *
		>(
			_state
		)
	);

	DWORD const offset(
		_ddoi->dwOfs
	);

	if(
		dinput::is_mouse_axis(
			offset
		)
	)
		instance.axis_[
			offset
		] =
			dinput::mouse_axis_code(
				offset
			);
	else
		instance.buttons_[
			offset
		] =
			dinput::mouse_button_code(
				offset
			);

	return DIENUM_CONTINUE;
}
