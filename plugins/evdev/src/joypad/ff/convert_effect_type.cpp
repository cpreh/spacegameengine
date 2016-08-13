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


#include <sge/evdev/joypad/ff/convert_effect_type.hpp>
#include <sge/input/joypad/ff/condition.hpp>
#include <sge/input/joypad/ff/condition_type.hpp>
#include <sge/input/joypad/ff/constant_fwd.hpp>
#include <sge/input/joypad/ff/periodic_fwd.hpp>
#include <sge/input/joypad/ff/ramp_fwd.hpp>
#include <sge/input/joypad/ff/variant.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


std::uint16_t
sge::evdev::joypad::ff::convert_effect_type(
	sge::input::joypad::ff::variant const &_variant
)
{
	return
		fcppt::cast::size<
			std::uint16_t
		>(
			fcppt::cast::to_unsigned(
				fcppt::variant::match(
					_variant,
					[](
						sge::input::joypad::ff::constant const &
					)
					{
						return
							FF_CONSTANT;
					},
					[](
						sge::input::joypad::ff::ramp const &
					)
					{
						return
							FF_RAMP;
					},
					[](
						sge::input::joypad::ff::periodic const &
					)
					{
						return
							FF_PERIODIC;
					},
					[](
						sge::input::joypad::ff::condition const &_condition
					)
					{
						switch(
							_condition.type()
						)
						{
						case sge::input::joypad::ff::condition_type::spring:
							return
								FF_SPRING;
						case sge::input::joypad::ff::condition_type::damper:
							return
								FF_DAMPER;
						case sge::input::joypad::ff::condition_type::inertia:
							return
								FF_INERTIA;
						case sge::input::joypad::ff::condition_type::friction:
							return
								FF_FRICTION;
						}

						FCPPT_ASSERT_UNREACHABLE;
					}
				)
			)
		);
}
