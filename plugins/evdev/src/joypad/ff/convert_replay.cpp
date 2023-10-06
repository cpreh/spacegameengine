//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/ff/convert_duration.hpp>
#include <sge/evdev/joypad/ff/convert_replay.hpp>
#include <sge/input/joypad/ff/delay.hpp>
#include <sge/input/joypad/ff/duration.hpp>
#include <sge/input/joypad/ff/optional_duration.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <limits>
#include <fcppt/config/external_end.hpp>

ff_replay sge::evdev::joypad::ff::convert_replay(
    sge::input::joypad::ff::optional_duration const &_opt_duration,
    sge::input::joypad::ff::delay const _delay)
{
  return ff_replay{
      fcppt::optional::maybe(
          _opt_duration,
          []
          {
            // TODO(philipp): What to put here?
            return std::numeric_limits<std::uint16_t>::max();
          },
          [](sge::input::joypad::ff::duration const _duration)
          { return sge::evdev::joypad::ff::convert_duration(_duration); }),
      sge::evdev::joypad::ff::convert_duration(_delay.get())};
}
