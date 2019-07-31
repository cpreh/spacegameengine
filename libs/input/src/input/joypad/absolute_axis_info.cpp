//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_max.hpp>
#include <sge/input/joypad/axis_min.hpp>
#include <fcppt/optional_string.hpp>


sge::input::joypad::absolute_axis_info::absolute_axis_info(
	sge::input::joypad::axis_code const _code,
	fcppt::optional_string const &_name,
	sge::input::joypad::axis_min const _min,
	sge::input::joypad::axis_max const _max
)
:
	code_(
		_code
	),
	name_(
		_name
	),
	min_(
		_min
	),
	max_(
		_max
	)
{
}

sge::input::joypad::axis_code
sge::input::joypad::absolute_axis_info::code() const
{
	return
		code_;
}

fcppt::optional_string const &
sge::input::joypad::absolute_axis_info::name() const
{
	return
		name_;
}

sge::input::joypad::axis_min
sge::input::joypad::absolute_axis_info::min() const
{
	return
		min_;
}

sge::input::joypad::axis_max
sge::input::joypad::absolute_axis_info::max() const
{
	return
		max_;
}
