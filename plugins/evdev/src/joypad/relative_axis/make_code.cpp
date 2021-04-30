//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/joypad/relative_axis/code.hpp>
#include <sge/evdev/joypad/relative_axis/make_code.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input-event-codes.h>
#include <fcppt/config/external_end.hpp>


sge::input::joypad::axis_code
sge::evdev::joypad::relative_axis::make_code(
	sge::evdev::joypad::relative_axis::code const _event
)
{
	switch(
		fcppt::cast::enum_to_int<
			sge::evdev::device::event_type_value
		>(
			_event
		)
	)
	{
	case REL_X:
		return sge::input::joypad::axis_code::x;
	case REL_Y:
		return sge::input::joypad::axis_code::y;
	case REL_Z:
		return sge::input::joypad::axis_code::z;
	case REL_RX:
	case REL_RY:
	case REL_RZ:
	case REL_HWHEEL:
	case REL_DIAL:
	case REL_WHEEL:
	case REL_MISC:
	default:
		return sge::input::joypad::axis_code::unknown;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
