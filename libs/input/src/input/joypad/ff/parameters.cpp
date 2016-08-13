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


#include <sge/input/joypad/ff/delay.hpp>
#include <sge/input/joypad/ff/direction.hpp>
#include <sge/input/joypad/ff/optional_duration.hpp>
#include <sge/input/joypad/ff/optional_trigger.hpp>
#include <sge/input/joypad/ff/parameters.hpp>
#include <sge/input/joypad/ff/variant.hpp>


sge::input::joypad::ff::parameters::parameters(
	sge::input::joypad::ff::direction const _direction,
	sge::input::joypad::ff::optional_trigger const &_trigger,
	sge::input::joypad::ff::optional_duration const &_duration,
	sge::input::joypad::ff::delay const _delay,
	sge::input::joypad::ff::variant const &_variant
)
:
	direction_{
		_direction
	},
	trigger_{
		_trigger
	},
	duration_{
		_duration
	},
	delay_{
		_delay
	},
	variant_{
		_variant
	}
{
}

sge::input::joypad::ff::direction
sge::input::joypad::ff::parameters::direction() const
{
	return
		direction_;
}

sge::input::joypad::ff::optional_trigger const &
sge::input::joypad::ff::parameters::trigger() const
{
	return
		trigger_;
}

sge::input::joypad::ff::optional_duration const &
sge::input::joypad::ff::parameters::duration() const
{
	return
		duration_;
}

sge::input::joypad::ff::delay
sge::input::joypad::ff::parameters::delay() const
{
	return
		delay_;
}

sge::input::joypad::ff::variant const &
sge::input::joypad::ff::parameters::variant() const
{
	return
		variant_;
}
