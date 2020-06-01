//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_BUTTON_EVENT_MAP_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_BUTTON_EVENT_MAP_HPP_INCLUDED

#include <sge/evdev/device/event_map.hpp>
#include <sge/input/joypad/button_id.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace button
{

using
event_map
=
sge::evdev::device::event_map<
	sge::input::joypad::button_id
>;

}
}
}
}

#endif
