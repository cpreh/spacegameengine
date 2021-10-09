//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/basic_info_impl.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>

template class sge::evdev::device::
    basic_info<sge::input::joypad::absolute_axis_id, sge::input::joypad::absolute_axis_info>;
