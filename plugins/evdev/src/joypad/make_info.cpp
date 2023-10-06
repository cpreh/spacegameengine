//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/name.hpp>
#include <sge/evdev/device/unique_id.hpp>
#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/make_info.hpp>
#include <sge/evdev/joypad/absolute_axis/info_container.hpp>
#include <sge/evdev/joypad/absolute_axis/make_info_container.hpp>
#include <sge/evdev/joypad/button/info_container.hpp>
#include <sge/evdev/joypad/button/make_info_container.hpp>
#include <sge/evdev/joypad/ff/make_info.hpp>
#include <sge/evdev/joypad/relative_axis/info_container.hpp>
#include <sge/evdev/joypad/relative_axis/make_info_container.hpp>
#include <sge/input/joypad/info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::evdev::joypad::info sge::evdev::joypad::make_info(sge::evdev::device::fd &_fd)
{
  sge::evdev::joypad::absolute_axis::info_container absolute_axis(
      sge::evdev::joypad::absolute_axis::make_info_container(_fd));

  sge::evdev::joypad::button::info_container buttons(
      sge::evdev::joypad::button::make_info_container(_fd));

  sge::evdev::joypad::relative_axis::info_container relative_axis(
      sge::evdev::joypad::relative_axis::make_info_container(_fd));

  return sge::evdev::joypad::info(
      sge::input::joypad::info(
          std::move(absolute_axis.infos()),
          std::move(buttons.infos()),
          std::move(relative_axis.infos()),
          sge::evdev::joypad::ff::make_info(_fd),
          sge::evdev::device::name(_fd),
          sge::evdev::device::unique_id(_fd)),
      sge::evdev::joypad::event_map(
          std::move(absolute_axis.event_map()),
          std::move(buttons.event_map()),
          std::move(relative_axis.event_map())));
}
