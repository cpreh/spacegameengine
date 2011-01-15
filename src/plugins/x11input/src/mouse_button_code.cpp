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


#include "../mouse_button_code.hpp"

sge::input::mouse::button_code::type
sge::x11input::mouse_button_code(
	int const _detail
)
{
	switch(
		_detail
	)
	{
	case 1:
		return sge::input::mouse::button_code::left;
	case 2:
		return sge::input::mouse::button_code::middle;
	case 3:
		return sge::input::mouse::button_code::right;
	case 4:
		return sge::input::mouse::button_code::_4;
	case 5:
		return sge::input::mouse::button_code::_5;
	case 6:
		return sge::input::mouse::button_code::_6;
	case 7:
		return sge::input::mouse::button_code::_7;
	case 8:
		return sge::input::mouse::button_code::_8;
	}
	
	return sge::input::mouse::button_code::unknown;
}
