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


#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/read_bits.hpp>
#include <sge/evdev/device/read_bits_result.hpp>
#include <sge/evdev/joypad/ff/make_info.hpp>
#include <sge/input/joypad/ff/type.hpp>
#include <sge/input/joypad/ff/type_field.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/bitfield/init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::evdev::device::event_type_value
to_linux_effect(
	sge::input::joypad::ff::type const _type
)
{
	switch(
		_type
	)
	{
	case sge::input::joypad::ff::type::constant:
		return
			FF_CONSTANT;
	case sge::input::joypad::ff::type::spring:
		return
			FF_SPRING;
	case sge::input::joypad::ff::type::friction:
		return
			FF_FRICTION;
	case sge::input::joypad::ff::type::damper:
		return
			FF_DAMPER;
	case sge::input::joypad::ff::type::inertia:
		return
			FF_RAMP;
	case sge::input::joypad::ff::type::ramp:
		return
			FF_SQUARE;
	case sge::input::joypad::ff::type::square:
		return
			FF_SINE;
	case sge::input::joypad::ff::type::sine:
		return
			FF_SINE;
	case sge::input::joypad::ff::type::saw_up:
		return
			FF_SAW_UP;
	case sge::input::joypad::ff::type::saw_down:
		return
			FF_SAW_DOWN;
	case sge::input::joypad::ff::type::custom:
		return
			FF_CUSTOM;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

}

sge::input::joypad::ff::type_field
sge::evdev::joypad::ff::make_info(
	sge::evdev::device::fd const &_fd
)
{
	sge::evdev::device::read_bits_result<
		FF_CNT
	> const result(
		sge::evdev::device::read_bits<
			FF_CNT
		>(
			_fd,
			EV_FF
		)
	);

	return
		fcppt::container::bitfield::init<
			sge::input::joypad::ff::type_field
		>(
			[
				&result
			](
				sge::input::joypad::ff::type const _value
			)
			{
				return
					result.get(
						to_linux_effect(
							_value
						)
					);
			}
		);
}
