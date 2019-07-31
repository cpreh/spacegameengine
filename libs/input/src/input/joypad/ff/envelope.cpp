//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/ff/attack_level.hpp>
#include <sge/input/joypad/ff/attack_time.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <sge/input/joypad/ff/fade_level.hpp>
#include <sge/input/joypad/ff/fade_time.hpp>


sge::input::joypad::ff::envelope::envelope(
	sge::input::joypad::ff::attack_level const _attack_level,
	sge::input::joypad::ff::attack_time const _attack_time,
	sge::input::joypad::ff::fade_level const _fade_level,
	sge::input::joypad::ff::fade_time const _fade_time
)
:
	attack_level_{
		_attack_level
	},
	attack_time_{
		_attack_time
	},
	fade_level_{
		_fade_level
	},
	fade_time_{
		_fade_time
	}
{
}

sge::input::joypad::ff::attack_level
sge::input::joypad::ff::envelope::attack_level() const
{
	return
		attack_level_;
}

sge::input::joypad::ff::attack_time
sge::input::joypad::ff::envelope::attack_time() const
{
	return
		attack_time_;
}

sge::input::joypad::ff::fade_level
sge::input::joypad::ff::envelope::fade_level() const
{
	return
		fade_level_;
}

sge::input::joypad::ff::fade_time
sge::input::joypad::ff::envelope::fade_time() const
{
	return
		fade_time_;
}
