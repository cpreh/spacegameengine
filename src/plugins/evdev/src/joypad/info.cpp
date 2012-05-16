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


#include <sge/evdev/joypad/fd_fwd.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>

#include <fcppt/text.hpp>


sge::input::joypad::info const
sge::evdev::joypad::info(
	sge::evdev::joypad::fd const &_fd
)
{
	return
		sge::input::joypad::info(
			sge::input::joypad::absolute_axis_info_container(
				sge::input::joypad::absolute_axis_info_container::vector()
			),
			sge::input::joypad::button_info_container(
				sge::input::joypad::button_info_container::vector()
			),
			sge::input::joypad::relative_axis_info_container(
				sge::input::joypad::relative_axis_info_container::vector()
			),
			sge::input::info::name(
				FCPPT_TEXT("TEST")
			)
		);
}
