//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/button/make_info.hpp>
#include <sge/evdev/joypad/button/make_string.hpp>
#include <sge/input/joypad/button_info.hpp>


sge::input::joypad::button_info
sge::evdev::joypad::button::make_info(
	sge::evdev::device::event_type const _event
)
{
	return
		sge::input::joypad::button_info(
			sge::evdev::joypad::button::make_string(
				_event
			)
		);
}
