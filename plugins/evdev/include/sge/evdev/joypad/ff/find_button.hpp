//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_FF_FIND_BUTTON_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_FIND_BUTTON_HPP_INCLUDED

#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/input/joypad/button_id.hpp>


namespace sge::evdev::joypad::ff
{

sge::evdev::device::event_type
find_button(
	sge::evdev::joypad::button::event_map const &,
	sge::input::joypad::button_id
);

}

#endif
