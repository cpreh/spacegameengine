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


#include <sge/dinput/mouse/device.hpp>
#include <sge/dinput/mouse/is_axis.hpp>
#include <sge/dinput/mouse/axis_code.hpp>
#include <sge/dinput/mouse/button_code.hpp>
#include <sge/dinput/di.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/button_id.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/info.hpp>
#include <fcppt/text.hpp>
#include <fcppt/signal/object_impl.hpp>


sge::dinput::mouse::device::device(
	dinput::device::parameters const &_param
)
:
	sge::input::mouse::device(),
	dinput::device::object(
		_param
	),
	// FIXME
	info_(
		sge::input::mouse::info(
			sge::input::mouse::axis_info_container(
				sge::input::mouse::axis_info_container::vector()
			),
			sge::input::mouse::button_info_container(
				sge::input::mouse::button_info_container::vector()
			),
			sge::input::info::name(
				FCPPT_TEXT("mouse")
			)
		)
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
}

sge::dinput::mouse::device::~device()
{
}

fcppt::signal::auto_connection
sge::dinput::mouse::device::axis_callback(
	input::mouse::axis_callback const &_callback
)
{
	return
		axis_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::mouse::device::button_callback(
	input::mouse::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

sge::input::mouse::info const &
sge::dinput::mouse::device::info() const
{
	return info_;
}

void
sge::dinput::mouse::device::dispatch()
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
			dinput::mouse::is_axis(
				offset
			)
		)
			axis_signal_(
				input::mouse::axis_event(
					input::mouse::axis(
						axis_[
							offset
						],
						input::mouse::axis_id(
							static_cast<
								sge::input::mouse::axis_id::value_type
							>(
								offset
							)
						)
					),
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
					input::mouse::button(
						buttons_[
							offset
						],
						sge::input::mouse::button_id(
							static_cast<
								sge::input::mouse::button_id::value_type
							>(
								offset
							)
						)
					),
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
sge::dinput::mouse::device::enum_mouse_keys(
	LPCDIDEVICEOBJECTINSTANCE _ddoi,
	LPVOID _state
)
{
	dinput::mouse::device &instance(
		dynamic_cast<
			dinput::mouse::device &
		>(
			*static_cast<
				dinput::device::object *
			>(
				_state
			)
		)
	);

	DWORD const offset(
		_ddoi->dwOfs
	);

	if(
		dinput::mouse::is_axis(
			offset
		)
	)
		instance.axis_[
			offset
		] =
			dinput::mouse::axis_code(
				offset
			);
	else
		instance.buttons_[
			offset
		] =
			dinput::mouse::button_code(
				offset
			);

	return DIENUM_CONTINUE;
}
