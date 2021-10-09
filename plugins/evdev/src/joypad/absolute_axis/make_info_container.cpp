//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/make_info_container.hpp>
#include <sge/evdev/device/read_bits.hpp>
#include <sge/evdev/joypad/absolute_axis/code.hpp>
#include <sge/evdev/joypad/absolute_axis/info_container.hpp>
#include <sge/evdev/joypad/absolute_axis/make_info.hpp>
#include <sge/evdev/joypad/absolute_axis/make_info_container.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input-event-codes.h>
#include <fcppt/config/external_end.hpp>

sge::evdev::joypad::absolute_axis::info_container
sge::evdev::joypad::absolute_axis::make_info_container(sge::evdev::device::fd &_fd)
{
  return sge::evdev::device::make_info_container<
      sge::input::joypad::absolute_axis_id,
      sge::input::joypad::absolute_axis_info,
      sge::evdev::joypad::absolute_axis::code>(
      sge::evdev::device::read_bits<sge::evdev::joypad::absolute_axis::code>(_fd, EV_ABS),
      [&_fd](sge::evdev::joypad::absolute_axis::code const _event)
      { return sge::evdev::joypad::absolute_axis::make_info(_fd, _event); });
}
