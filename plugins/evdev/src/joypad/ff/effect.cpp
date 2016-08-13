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


#include <sge/evdev/device/event_value.hpp>
#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/evdev/joypad/ff/convert_effect.hpp>
#include <sge/evdev/joypad/ff/effect.hpp>
#include <sge/evdev/joypad/ff/write_event.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/optional_play_count.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/input/joypad/ff/play_count.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <limits>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::ff::effect::effect(
	sge::evdev::device::fd const &_fd,
	sge::evdev::joypad::button::event_map const &_buttons,
	sge::input::joypad::ff::parameters const &_parameters
)
:
	sge::input::joypad::ff::effect(),
	fd_{
		_fd
	},
	uploaded_effect_{
		_fd,
		sge::evdev::joypad::ff::convert_effect(
			_buttons,
			_parameters
		)
	}
{
}

sge::evdev::joypad::ff::effect::~effect()
{
}

void
sge::evdev::joypad::ff::effect::play(
	sge::input::joypad::ff::optional_play_count const _opt_play_count
)
{
	sge::evdev::joypad::ff::write_event(
		fd_,
		uploaded_effect_.id(),
		fcppt::optional::maybe(
			_opt_play_count,
			[]{
				// TODO: What do we put here?
				return
					std::numeric_limits<
						sge::evdev::device::event_value
					>::max();
			},
			[](
				sge::input::joypad::ff::play_count const _play_count
			)
			{
				return
					fcppt::cast::size<
						sge::evdev::device::event_value
					>(
						fcppt::cast::to_signed(
							_play_count.get()
						)
					);
			}
		)
	);
}

void
sge::evdev::joypad::ff::effect::stop()
{
	sge::evdev::joypad::ff::write_event(
		fd_,
		uploaded_effect_.id(),
		fcppt::literal<
			sge::evdev::device::event_value
		>(
			0
		)
	);
}
