/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../cast_key.hpp"
#include "../di.hpp"

sge::input::mouse::button_code::type
sge::dinput::mouse_button_code(
	DWORD const _code
)
{
	if(
		_code == dinput::cast_key(DIMOFS_BUTTON0)
	)
		return sge::input::mouse::button_code::left;
	else if(
		_code == dinput::cast_key(DIMOFS_BUTTON1)
	)
		return sge::input::mouse::button_code::right;
	else if(
		_code == dinput::cast_key(DIMOFS_BUTTON2)
	)
		return sge::input::mouse::button_code::middle;
	else if(
		_code == dinput::cast_key(DIMOFS_BUTTON3)
	)
		return sge::input::mouse::button_code::_4;
	else if(
		_code == dinput::cast_key(DIMOFS_BUTTON4)
	)
		return sge::input::mouse::button_code::_5;
	else if(
		_code == dinput::cast_key(DIMOFS_BUTTON5)
	)
		return sge::input::mouse::button_code::_6;
	else if(
		_code == dinput::cast_key(DIMOFS_BUTTON6)
	)
		return sge::input::mouse::button_code::_7;
	else if(
		_code == dinput::cast_key(DIMOFS_BUTTON7)
	)
		return sge::input::mouse::button_code::_8;

	return sge::input::mouse::button_code::unknown;
}
