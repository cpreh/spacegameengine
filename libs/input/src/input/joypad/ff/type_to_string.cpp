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


#include <sge/input/joypad/ff/type.hpp>
#include <sge/input/joypad/ff/type_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string
sge::input::joypad::ff::type_to_string(
	sge::input::joypad::ff::type const _type
)
{
#define SGE_FF_TYPE_TO_STRING_CASE(\
	name \
) \
	case sge::input::joypad::ff::type:: name: \
		return \
			FCPPT_TEXT(\
				#name \
			)

	switch(
		_type
	)
	{
		SGE_FF_TYPE_TO_STRING_CASE(
			constant
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			spring
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			friction
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			damper
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			inertia
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			ramp
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			square
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			sine
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			saw_up
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			saw_down
		);
		SGE_FF_TYPE_TO_STRING_CASE(
			custom
		);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
