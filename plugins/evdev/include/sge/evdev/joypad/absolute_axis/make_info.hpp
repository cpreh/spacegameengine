//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_ABSOLUTE_AXIS_MAKE_INFO_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_ABSOLUTE_AXIS_MAKE_INFO_HPP_INCLUDED

#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/input/joypad/absolute_axis_info_fwd.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace absolute_axis
{

sge::input::joypad::absolute_axis_info
make_info(
	sge::evdev::device::fd &, // NOLINT(google-runtime-references)
	sge::evdev::device::event_type
);

}
}
}
}

#endif
