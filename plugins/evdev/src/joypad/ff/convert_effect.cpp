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


#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/evdev/joypad/ff/convert_effect.hpp>
#include <sge/evdev/joypad/ff/convert_effect_type.hpp>
#include <sge/evdev/joypad/ff/convert_replay.hpp>
#include <sge/evdev/joypad/ff/convert_trigger.hpp>
#include <sge/evdev/joypad/ff/convert_variant.hpp>
#include <sge/input/joypad/ff/parameters.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


ff_effect
sge::evdev::joypad::ff::convert_effect(
	sge::evdev::joypad::button::event_map const &_buttons,
	sge::input::joypad::ff::parameters const &_parameters
)
{
	return
		ff_effect{
			sge::evdev::joypad::ff::convert_effect_type(
				_parameters.variant()
			),
			// ID
			fcppt::literal<
				std::int16_t
			>(
				-1
			),
			fcppt::cast::size<
				std::uint16_t
			>(
				_parameters.direction().get().get()
				/
				1000u
			),
			sge::evdev::joypad::ff::convert_trigger(
				_buttons,
				_parameters.trigger()
			),
			sge::evdev::joypad::ff::convert_replay(
				_parameters.duration(),
				_parameters.delay()
			),
			sge::evdev::joypad::ff::convert_variant(
				_parameters.variant()
			)
		};
}
