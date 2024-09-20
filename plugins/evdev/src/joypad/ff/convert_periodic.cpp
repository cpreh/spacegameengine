//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/ff/convert_duration.hpp>
#include <sge/evdev/joypad/ff/convert_envelope.hpp>
#include <sge/evdev/joypad/ff/convert_periodic.hpp>
#include <sge/evdev/joypad/ff/convert_waveform.hpp>
#include <sge/input/joypad/ff/periodic.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

ff_periodic_effect
sge::evdev::joypad::ff::convert_periodic(sge::input::joypad::ff::periodic const &_periodic)
{
  return ff_periodic_effect{
      .waveform = sge::evdev::joypad::ff::convert_waveform(_periodic.waveform()),
      .period = sge::evdev::joypad::ff::convert_duration(_periodic.period().get()),
      .magnitude = fcppt::cast::size<std::int16_t>(_periodic.magnitude().get()),
      .offset = fcppt::cast::size<std::int16_t>(_periodic.offset().get()),
      .phase = fcppt::cast::size<std::uint16_t>(_periodic.phase().get()),
      .envelope = sge::evdev::joypad::ff::convert_envelope(_periodic.envelope()),
      .custom_len = fcppt::literal<std::uint32_t>(0),
      .custom_data = nullptr};
}
