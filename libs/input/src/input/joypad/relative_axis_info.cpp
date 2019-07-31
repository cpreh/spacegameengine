//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <fcppt/optional_string.hpp>


sge::input::joypad::relative_axis_info::relative_axis_info(
	sge::input::joypad::axis_code const _code,
	fcppt::optional_string const &_name
)
:
	code_(
		_code
	),
	name_(
		_name
	)
{
}

sge::input::joypad::axis_code
sge::input::joypad::relative_axis_info::code() const
{
	return
		code_;
}

fcppt::optional_string const &
sge::input::joypad::relative_axis_info::name() const
{
	return
		name_;
}
