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
#include <sge/evdev/joypad/info.hpp>
#include <sge/input/joypad/info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::info::info(
	sge::input::joypad::info &&_input_info,
	sge::evdev::joypad::event_map &&_event_map
)
:
	input_info_(
		std::move(
			_input_info
		)
	),
	event_map_(
		std::move(
			_event_map
		)
	)
{
}

sge::input::joypad::info const &
sge::evdev::joypad::info::input_info() const
{
	return
		input_info_;
}

sge::evdev::joypad::event_map const &
sge::evdev::joypad::info::event_map() const
{
	return
		event_map_;
}
