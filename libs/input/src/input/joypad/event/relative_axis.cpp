//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/base.hpp>
#include <sge/input/joypad/event/relative_axis.hpp>


sge::input::joypad::event::relative_axis::relative_axis(
	sge::input::joypad::shared_ptr const _joypad,
	sge::input::joypad::relative_axis const &_axis,
	sge::input::joypad::axis_value const _axis_value
)
:
	sge::input::joypad::event::base{
		_joypad
	},
	axis_{
		_axis
	},
	axis_value_{
		_axis_value
	}
{
}

sge::input::joypad::event::relative_axis::~relative_axis()
{
}

sge::input::joypad::relative_axis const &
sge::input::joypad::event::relative_axis::axis() const
{
	return
		axis_;
}

sge::input::joypad::axis_value
sge::input::joypad::event::relative_axis::value() const
{
	return
		axis_value_;
}
