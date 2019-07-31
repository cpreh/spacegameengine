//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/ff/constant.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <sge/input/joypad/ff/magnitude.hpp>


sge::input::joypad::ff::constant::constant(
	sge::input::joypad::ff::magnitude const _magnitude,
	sge::input::joypad::ff::envelope const &_envelope
)
:
	magnitude_{
		_magnitude
	},
	envelope_{
		_envelope
	}
{
}

sge::input::joypad::ff::magnitude
sge::input::joypad::ff::constant::magnitude() const
{
	return
		magnitude_;
}

sge::input::joypad::ff::envelope const &
sge::input::joypad::ff::constant::envelope() const
{
	return
		envelope_;
}
