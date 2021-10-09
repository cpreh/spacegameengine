//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/ff/convert_duration.hpp>
#include <sge/evdev/joypad/ff/convert_envelope.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

ff_envelope
sge::evdev::joypad::ff::convert_envelope(sge::input::joypad::ff::envelope const &_envelope)
{
  return ff_envelope{
      sge::evdev::joypad::ff::convert_duration(_envelope.attack_time().get()),
      fcppt::cast::size<std::uint16_t>(_envelope.attack_level().get()),
      sge::evdev::joypad::ff::convert_duration(_envelope.fade_time().get()),
      fcppt::cast::size<std::uint16_t>(_envelope.fade_level().get())};
}
