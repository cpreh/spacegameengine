//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/input/joypad/info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::evdev::joypad::info::info(
    sge::input::joypad::info &&_input_info, sge::evdev::joypad::event_map &&_event_map)
    : input_info_(std::move(_input_info)), event_map_(std::move(_event_map))
{
}

sge::input::joypad::info const &sge::evdev::joypad::info::input_info() const { return input_info_; }

sge::evdev::joypad::event_map const &sge::evdev::joypad::info::event_map() const
{
  return event_map_;
}
