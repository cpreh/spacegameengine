//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_code_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string
sge::input::joypad::axis_code_to_string(
	sge::input::joypad::axis_code const _code
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
