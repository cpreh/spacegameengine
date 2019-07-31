//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/ff/trigger.hpp>
#include <sge/input/joypad/ff/trigger_cooldown.hpp>


sge::input::joypad::ff::trigger::trigger(
	sge::input::joypad::button_id const _button,
	sge::input::joypad::ff::trigger_cooldown const _cooldown
)
:
	button_{
		_button
	},
	cooldown_{
		_cooldown
	}
{
}

sge::input::joypad::button_id
sge::input::joypad::ff::trigger::button() const
{
	return
		button_;
}

sge::input::joypad::ff::trigger_cooldown
sge::input::joypad::ff::trigger::cooldown() const
{
	return
		cooldown_;
}
