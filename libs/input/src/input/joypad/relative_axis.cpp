//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>


sge::input::joypad::relative_axis::relative_axis(
	sge::input::joypad::axis_code const _code,
	sge::input::joypad::relative_axis_id const _id
)
:
	code_(
		_code
	),
	id_(
		_id
	)
{
}

sge::input::joypad::axis_code
sge::input::joypad::relative_axis::code() const
{
	return
		code_;
}

sge::input::joypad::relative_axis_id
sge::input::joypad::relative_axis::id() const
{
	return
		id_;
}
