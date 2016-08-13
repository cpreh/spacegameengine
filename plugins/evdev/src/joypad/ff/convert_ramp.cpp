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


#include <sge/evdev/joypad/ff/convert_envelope.hpp>
#include <sge/evdev/joypad/ff/convert_ramp.hpp>
#include <sge/input/joypad/ff/ramp.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


ff_ramp_effect
sge::evdev::joypad::ff::convert_ramp(
	sge::input::joypad::ff::ramp const &_ramp
)
{
	return
		ff_ramp_effect{
			fcppt::cast::size<
				std::int16_t
			>(
				_ramp.start_magnitude().get()
			),
			fcppt::cast::size<
				std::int16_t
			>(
				_ramp.end_magnitude().get()
			),
			sge::evdev::joypad::ff::convert_envelope(
				_ramp.envelope()
			)
		};
}
