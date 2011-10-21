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


#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_code_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string const
sge::input::joypad::axis_code_to_string(
	joypad::axis_code::type const _code
)
{
#define MAKE_CASE(\
	name\
)\
case sge::input::joypad::axis_code::name:\
	return FCPPT_TEXT(#name);

	switch(
		_code
	)
	{
	MAKE_CASE(x)
	MAKE_CASE(y)
	MAKE_CASE(z)
	MAKE_CASE(unknown)
	}

	FCPPT_ASSERT_UNREACHABLE;
}
