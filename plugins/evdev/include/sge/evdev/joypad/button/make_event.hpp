//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_BUTTON_MAKE_EVENT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_BUTTON_MAKE_EVENT_HPP_INCLUDED

#include <sge/evdev/device/event_fwd.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_info_container_fwd.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>

namespace sge::evdev::joypad::button
{

awl::event::optional_base_unique_ptr make_event(
    sge::input::joypad::shared_ptr const &,
    sge::input::joypad::button_id,
    sge::input::joypad::button_info_container const &,
    sge::evdev::device::event);

}

#endif
