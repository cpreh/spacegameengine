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


#include <sge/dinput/cast_key.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_code.hpp>


sge::input::joypad::axis_code
sge::dinput::joypad::axis_code(
	DWORD const _code
)
{
	if(
		_code == sge::dinput::cast_key(DIMOFS_X)
	)
		return sge::input::joypad::axis_code::x;
	else if(
		_code == sge::dinput::cast_key(DIMOFS_Y)
	)
		return sge::input::joypad::axis_code::y;
	else if(
		_code ==sge:: dinput::cast_key(DIMOFS_Z)
	)
		return sge::input::joypad::axis_code::z;

	return sge::input::joypad::axis_code::unknown;
}
