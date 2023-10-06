//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/is_joypad.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <fcppt/loop.hpp>
#include <fcppt/algorithm/fold_break.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input-event-codes.h>
#include <utility>
#include <fcppt/config/external_end.hpp>

bool sge::evdev::joypad::is_joypad(sge::evdev::joypad::info const &_info)
{
  return fcppt::algorithm::fold_break(
      _info.event_map().buttons(),
      false,
      [](std::pair<sge::evdev::device::event_type, sge::input::joypad::button_id> const _element,
         bool const _has_joypad_buttons)
      {
        int const value(fcppt::cast::to_signed(_element.first.get()));

        if (value >= BTN_MOUSE && value <= BTN_TASK)
        {
          return std::make_pair(fcppt::loop::break_, false);
        }

        if (value >= BTN_JOYSTICK && value < BTN_DIGI)
        {
          return std::make_pair(fcppt::loop::continue_, true);
        }

        return std::make_pair(fcppt::loop::continue_, _has_joypad_buttons);
      });
}
