//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/ff/convert_condition.hpp>
#include <sge/input/joypad/ff/condition.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

ff_condition_effect
sge::evdev::joypad::ff::convert_condition(sge::input::joypad::ff::condition const &_condition)
{
  return ff_condition_effect{
      .right_saturation = fcppt::cast::size<std::uint16_t>(_condition.right_saturation().get()),
      .left_saturation = fcppt::cast::size<std::uint16_t>(_condition.left_saturation().get()),
      .right_coeff = fcppt::cast::size<std::int16_t>(_condition.right_coefficient().get()),
      .left_coeff = fcppt::cast::size<std::int16_t>(_condition.left_coefficient().get()),
      .deadband = fcppt::cast::size<std::uint16_t>(_condition.deadband_size().get()),
      .center = fcppt::cast::size<std::int16_t>(_condition.deadband_center().get())};
}
