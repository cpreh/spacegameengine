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
