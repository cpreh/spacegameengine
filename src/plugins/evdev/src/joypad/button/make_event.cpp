/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/evdev/device/event.hpp>
#include <sge/evdev/joypad/button/make_event.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_info_container_fwd.hpp>


sge::input::joypad::button_event const
sge::evdev::joypad::button::make_event(
	sge::input::joypad::button_id const _id,
	sge::input::joypad::button_info_container const &,
	sge::evdev::device::event const _event
)
{
	return
		sge::input::joypad::button_event(
			_id,
			_event.get().value != 0u
		);
}
