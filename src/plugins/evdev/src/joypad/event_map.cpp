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


#include <sge/evdev/joypad/event_map.hpp>


sge::evdev::joypad::event_map::event_map(
	sge::evdev::joypad::event_map::absolute_axis_map const &_absolute_axis,
	sge::evdev::joypad::event_map::button_map const &_buttons,
	sge::evdev::joypad::event_map::relative_axis_map const &_relative_axis
)
:
	absolute_axis_(
		_absolute_axis
	),
	buttons_(
		_buttons
	),
	relative_axis_(
		_relative_axis
	)
{
}

sge::evdev::joypad::event_map::absolute_axis_map const &
sge::evdev::joypad::event_map::absolute_axis() const
{
	return
		absolute_axis_;
}

sge::evdev::joypad::event_map::button_map const &
sge::evdev::joypad::event_map::buttons() const
{
	return
		buttons_;
}

sge::evdev::joypad::event_map::relative_axis_map const &
sge::evdev::joypad::event_map::relative_axis() const
{
	return
		relative_axis_;
}
