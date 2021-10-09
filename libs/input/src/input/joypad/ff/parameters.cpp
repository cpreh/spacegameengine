//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/ff/delay.hpp>
#include <sge/input/joypad/ff/direction.hpp>
#include <sge/input/joypad/ff/optional_duration.hpp>
#include <sge/input/joypad/ff/optional_trigger.hpp>
#include <sge/input/joypad/ff/parameters.hpp>
#include <sge/input/joypad/ff/variant.hpp>

sge::input::joypad::ff::parameters::parameters(
    sge::input::joypad::ff::direction const _direction,
    sge::input::joypad::ff::optional_trigger const &_trigger,
    sge::input::joypad::ff::optional_duration const &_duration,
    sge::input::joypad::ff::delay const _delay,
    sge::input::joypad::ff::variant const &_variant)
    : direction_{_direction},
      trigger_{_trigger},
      duration_{_duration},
      delay_{_delay},
      variant_{_variant}
{
}

sge::input::joypad::ff::direction sge::input::joypad::ff::parameters::direction() const
{
  return direction_;
}

sge::input::joypad::ff::optional_trigger const &sge::input::joypad::ff::parameters::trigger() const
{
  return trigger_;
}

sge::input::joypad::ff::optional_duration const &
sge::input::joypad::ff::parameters::duration() const
{
  return duration_;
}

sge::input::joypad::ff::delay sge::input::joypad::ff::parameters::delay() const { return delay_; }

sge::input::joypad::ff::variant const &sge::input::joypad::ff::parameters::variant() const
{
  return variant_;
}
