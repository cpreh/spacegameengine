/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/key/code.hpp>
#include <sge/input/key/code_to_digit.hpp>
#include <sge/input/key/digit.hpp>
#include <sge/input/key/optional_digit.hpp>


sge::input::key::optional_digit
sge::input::key::code_to_digit(
	sge::input::key::code const _code
)
{
#define CONVERT_KEYCODE_TO_DIGIT(\
	num\
) \
case sge::input::key::code::_ ## num: \
	return \
		sge::input::key::optional_digit(\
			sge::input::key::digit(\
				num ## u \
			) \
		)

	switch(
		_code
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
		return
			sge::input::key::optional_digit();
	}
}
