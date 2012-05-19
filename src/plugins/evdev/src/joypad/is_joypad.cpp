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


#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/is_joypad.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


bool
sge::evdev::joypad::is_joypad(
	sge::evdev::joypad::info const &_info
)
{
	bool has_joypad_buttons(
		false
	);

	sge::evdev::joypad::event_map::button_map const &buttons(
		_info.event_map().buttons()
	);

	for(
		sge::evdev::joypad::event_map::button_map::const_iterator it(
			buttons.begin()
		);
		it != buttons.end();
		++it
	)
	{
		int const value(
			static_cast<
				int
			>(
				it->first.get()
			)
		);

		if(
			value
			>= BTN_MOUSE
			&&
			value
			<= BTN_TASK
		)
			return false;

		if(
			value
			>= BTN_JOYSTICK
			&&
			value
			< BTN_DIGI
		)
			has_joypad_buttons = true;
	}

	return
		has_joypad_buttons;
}
