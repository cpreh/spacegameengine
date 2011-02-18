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


#include <sge/input/keyboard/key_code_to_digit.hpp>
#include <fcppt/optional_impl.hpp>

sge::input::keyboard::optional_digit const
sge::input::keyboard::key_code_to_digit(
	key_code::type const _key_code
)
{
	switch(
		_key_code
	)
	{
	case sge::input::keyboard::key_code::_0:
		return keyboard::digit(0u);
	case sge::input::keyboard::key_code::_1:
		return keyboard::digit(1u);
	case sge::input::keyboard::key_code::_2:
		return keyboard::digit(2u);
	case sge::input::keyboard::key_code::_3:
		return keyboard::digit(3u);
	case sge::input::keyboard::key_code::_4:
		return keyboard::digit(4u);
	case sge::input::keyboard::key_code::_5:
		return keyboard::digit(5u);
	case sge::input::keyboard::key_code::_6:
		return keyboard::digit(6u);
	case sge::input::keyboard::key_code::_7:
		return keyboard::digit(7u);
	case sge::input::keyboard::key_code::_8:
		return keyboard::digit(8u);
	case sge::input::keyboard::key_code::_9:
		return keyboard::digit(9u);
	default:
		return keyboard::optional_digit();
	}
}
