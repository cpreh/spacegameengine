//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/ff/convert_constant.hpp>
#include <sge/evdev/joypad/ff/convert_envelope.hpp>
#include <sge/input/joypad/ff/constant.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

ff_constant_effect
sge::evdev::joypad::ff::convert_constant(sge::input::joypad::ff::constant const &_constant)
{
  return ff_constant_effect{
      fcppt::cast::size<std::int16_t>(_constant.magnitude().get()),
      sge::evdev::joypad::ff::convert_envelope(_constant.envelope())};
}
