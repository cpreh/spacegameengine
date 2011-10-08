/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>

sge::input::joypad::info::info(
	input::joypad::absolute_axis_info_container const &_absolute_axis,
	input::joypad::button_info_container const &_buttons,
	input::joypad::relative_axis_info_container const &_relative_axis
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

sge::input::joypad::absolute_axis_info_container const &
sge::input::joypad::info::absolute_axis() const
{
	return absolute_axis_;
}

sge::input::joypad::button_info_container const &
sge::input::joypad::info::buttons() const
{
	return buttons_;
}

sge::input::joypad::relative_axis_info_container const &
sge::input::joypad::info::relative_axis() const
{
	return relative_axis_;
}
