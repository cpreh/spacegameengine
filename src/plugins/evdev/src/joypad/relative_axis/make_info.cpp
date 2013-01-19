/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/relative_axis/make_code.hpp>
#include <sge/evdev/joypad/relative_axis/make_info.hpp>
#include <sge/evdev/joypad/relative_axis/make_string.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>


sge::input::joypad::relative_axis_info const
sge::evdev::joypad::relative_axis::make_info(
	sge::evdev::device::event_type const _event
)
{
	return
		sge::input::joypad::relative_axis_info(
			sge::evdev::joypad::relative_axis::make_code(
				_event
			),
			sge::evdev::joypad::relative_axis::make_string(
				_event
			)
		);
}
