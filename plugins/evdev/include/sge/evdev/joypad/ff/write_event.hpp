//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_FF_WRITE_EVENT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_WRITE_EVENT_HPP_INCLUDED

#include <sge/evdev/device/event_value.hpp>
#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/joypad/ff/id.hpp>

namespace sge::evdev::joypad::ff
{

void write_event(
    sge::evdev::device::fd &, // NOLINT(google-runtime-references)
    sge::evdev::joypad::ff::id,
    sge::evdev::device::event_value);

}

#endif
