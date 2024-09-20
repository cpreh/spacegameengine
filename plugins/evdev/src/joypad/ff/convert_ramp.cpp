//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/ff/convert_envelope.hpp>
#include <sge/evdev/joypad/ff/convert_ramp.hpp>
#include <sge/input/joypad/ff/ramp.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

ff_ramp_effect sge::evdev::joypad::ff::convert_ramp(sge::input::joypad::ff::ramp const &_ramp)
{
  return ff_ramp_effect{
      .start_level = fcppt::cast::size<std::int16_t>(_ramp.start_magnitude().get()),
      .end_level = fcppt::cast::size<std::int16_t>(_ramp.end_magnitude().get()),
      .envelope = sge::evdev::joypad::ff::convert_envelope(_ramp.envelope())};
}
