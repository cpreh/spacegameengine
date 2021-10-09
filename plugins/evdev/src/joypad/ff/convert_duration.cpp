//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/ff/convert_duration.hpp>
#include <sge/input/joypad/ff/duration.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <cstdint>
#include <ratio>
#include <fcppt/config/external_end.hpp>

std::uint16_t
sge::evdev::joypad::ff::convert_duration(sge::input::joypad::ff::duration const &_duration)
{
  return std::chrono::duration_cast<std::chrono::duration<std::uint16_t, std::milli>>(_duration)
      .count();
}
