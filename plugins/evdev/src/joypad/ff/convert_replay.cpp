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


#include <sge/evdev/joypad/ff/convert_duration.hpp>
#include <sge/evdev/joypad/ff/convert_replay.hpp>
#include <sge/input/joypad/ff/delay.hpp>
#include <sge/input/joypad/ff/duration.hpp>
#include <sge/input/joypad/ff/optional_duration.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <limits>
#include <fcppt/config/external_end.hpp>


ff_replay
sge::evdev::joypad::ff::convert_replay(
	sge::input::joypad::ff::optional_duration const &_opt_duration,
	sge::input::joypad::ff::delay const _delay
)
{
	return
		ff_replay{
			fcppt::optional::maybe(
				_opt_duration,
				[]{
					// TODO: What to put here?
					return
						std::numeric_limits<
							std::uint16_t
						>::max();
				},
				[](
					sge::input::joypad::ff::duration const _duration
				)
				{
					return
						sge::evdev::joypad::ff::convert_duration(
							_duration
						);
				}
			),
			sge::evdev::joypad::ff::convert_duration(
				_delay.get()
			)
		};
}
