//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_ABSOLUTE_AXIS_INFO_CONTAINER_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_ABSOLUTE_AXIS_INFO_CONTAINER_HPP_INCLUDED

#include <sge/evdev/device/basic_info_decl.hpp>
#include <sge/evdev/joypad/absolute_axis/info_container_fwd.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>


extern
template
class
sge::evdev::device::basic_info<
	sge::input::joypad::absolute_axis_id,
	sge::input::joypad::absolute_axis_info
>;

#endif
