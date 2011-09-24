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


#include <sge/x11input/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::joypad::axis_code::type
sge::x11input::joypad::axis_code(
	XIValuatorClassInfo const &_info
)
{
	switch(
		_info.number
	)
	{
	case 0:
		return sge::input::joypad::axis_code::x;
	case 1:
		return sge::input::joypad::axis_code::x;
	case 2:
		return sge::input::joypad::axis_code::z;
	default:
		return sge::input::joypad::axis_code::unknown;
	}
}
