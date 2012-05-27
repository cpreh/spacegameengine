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


#include <sge/dinput/joypad/absolute_axis_map.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/info.hpp>
#include <sge/dinput/joypad/relative_axis_map.hpp>
#include <sge/input/joypad/info.hpp>
	

sge::dinput::joypad::info::info(
	sge::input::joypad::info const &_input_info,
	sge::dinput::joypad::absolute_axis_map const &_absolute_axis_map,
	sge::dinput::joypad::button_map const &_button_map,
	sge::dinput::joypad::relative_axis_map const &_relative_axis_map
)
:
	input_info_(
		_input_info
	),
	absolute_axis_map_(
		_absolute_axis_map
	),
	button_map_(
		_button_map
	),
	relative_axis_map_(
		_relative_axis_map
	)
{
}

sge::input::joypad::info const &
sge::dinput::joypad::info::input_info() const
{
	return
		input_info_;
}

sge::dinput::joypad::absolute_axis_map const &
sge::dinput::joypad::info::absolute_axis_map() const
{
	return
		absolute_axis_map_;
}

sge::dinput::joypad::button_map const &
sge::dinput::joypad::info::button_map() const
{
	return
		button_map_;
}
	
sge::dinput::joypad::relative_axis_map const &
sge::dinput::joypad::info::relative_axis_map() const
{
	return
		relative_axis_map_;
}
