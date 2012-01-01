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


#include <sge/input/keyboard/digit.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_code_to_digit.hpp>
#include <sge/input/keyboard/optional_digit.hpp>
#include <fcppt/optional_impl.hpp>


sge::input::keyboard::optional_digit const
sge::input::keyboard::key_code_to_digit(
	key_code::type const _key_code
)
{
#define CONVERT_KEYCODE_TO_DIGIT(\
	num\
) \
case sge::input::keyboard::key_code::_ ## num: \
	return \
		sge::input::keyboard::optional_digit(\
			sge::input::keyboard::digit(\
				num ## u \
			) \
		)

	switch(
		_key_code
	)
	{
	CONVERT_KEYCODE_TO_DIGIT(0);
	CONVERT_KEYCODE_TO_DIGIT(1);
	CONVERT_KEYCODE_TO_DIGIT(2);
	CONVERT_KEYCODE_TO_DIGIT(3);
	CONVERT_KEYCODE_TO_DIGIT(4);
	CONVERT_KEYCODE_TO_DIGIT(5);
	CONVERT_KEYCODE_TO_DIGIT(6);
	CONVERT_KEYCODE_TO_DIGIT(7);
	CONVERT_KEYCODE_TO_DIGIT(8);
	CONVERT_KEYCODE_TO_DIGIT(9);
	default:
		return keyboard::optional_digit();
	}
}
