//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_JOYPAD_BUTTON_INFO_CONTAINER_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_BUTTON_INFO_CONTAINER_HPP_INCLUDED

#include <sge/evdev/device/basic_info_decl.hpp>
#include <sge/evdev/joypad/button/info_container_fwd.hpp> // IWYU pragma: export
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <sge/input/joypad/button_info_container.hpp>

extern template class sge::evdev::device::
    basic_info<sge::input::joypad::button_id, sge::input::joypad::button_info>;

#endif
