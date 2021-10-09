//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/event_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::evdev::joypad::event_map::event_map(
    sge::evdev::joypad::event_map::absolute_axis_map &&_absolute_axis,
    sge::evdev::joypad::event_map::button_map &&_buttons,
    sge::evdev::joypad::event_map::relative_axis_map &&_relative_axis)
    : absolute_axis_(std::move(_absolute_axis)),
      buttons_(std::move(_buttons)),
      relative_axis_(std::move(_relative_axis))
{
}

sge::evdev::joypad::event_map::absolute_axis_map const &
sge::evdev::joypad::event_map::absolute_axis() const
{
  return absolute_axis_;
}

sge::evdev::joypad::event_map::button_map const &sge::evdev::joypad::event_map::buttons() const
{
  return buttons_;
}

sge::evdev::joypad::event_map::relative_axis_map const &
sge::evdev::joypad::event_map::relative_axis() const
{
  return relative_axis_;
}
