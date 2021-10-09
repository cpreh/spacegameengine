//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/ff/convert_condition.hpp>
#include <sge/evdev/joypad/ff/convert_constant.hpp>
#include <sge/evdev/joypad/ff/convert_periodic.hpp>
#include <sge/evdev/joypad/ff/convert_ramp.hpp>
#include <sge/evdev/joypad/ff/convert_variant.hpp>
#include <sge/evdev/joypad/ff/variant.hpp>
#include <sge/input/joypad/ff/condition_fwd.hpp>
#include <sge/input/joypad/ff/constant_fwd.hpp>
#include <sge/input/joypad/ff/periodic_fwd.hpp>
#include <sge/input/joypad/ff/ramp_fwd.hpp>
#include <sge/input/joypad/ff/variant.hpp>
#include <fcppt/variant/match.hpp>

sge::evdev::joypad::ff::variant
sge::evdev::joypad::ff::convert_variant(sge::input::joypad::ff::variant const &_variant)
{
  sge::evdev::joypad::ff::variant result;

  fcppt::variant::match(
      _variant,
      [&result](sge::input::joypad::ff::constant const &_constant)
      { result.constant = sge::evdev::joypad::ff::convert_constant(_constant); },
      [&result](sge::input::joypad::ff::ramp const &_ramp)
      { result.ramp = sge::evdev::joypad::ff::convert_ramp(_ramp); },
      [&result](sge::input::joypad::ff::periodic const &_periodic)
      { result.periodic = sge::evdev::joypad::ff::convert_periodic(_periodic); },
      [&result](sge::input::joypad::ff::condition const &_condition)
      {
        // TODO(philipp): Should we separate this?

        ff_condition_effect const effect(sge::evdev::joypad::ff::convert_condition(_condition));

        result.condition[0] = effect;

        result.condition[1] = effect;
      });

  return result;
}
