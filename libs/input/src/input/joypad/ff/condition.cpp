//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/ff/condition.hpp>
#include <sge/input/joypad/ff/condition_type.hpp>
#include <sge/input/joypad/ff/deadband_center.hpp>
#include <sge/input/joypad/ff/deadband_size.hpp>
#include <sge/input/joypad/ff/left_coefficient.hpp>
#include <sge/input/joypad/ff/left_saturation.hpp>
#include <sge/input/joypad/ff/right_coefficient.hpp>
#include <sge/input/joypad/ff/right_saturation.hpp>

sge::input::joypad::ff::condition::condition(
    sge::input::joypad::ff::condition_type const _type,
    sge::input::joypad::ff::left_coefficient const _left_coefficient,
    sge::input::joypad::ff::right_coefficient const _right_coefficient,
    sge::input::joypad::ff::left_saturation const _left_saturation,
    sge::input::joypad::ff::right_saturation const _right_saturation,
    sge::input::joypad::ff::deadband_center const _deadband_center,
    sge::input::joypad::ff::deadband_size const _deadband_size)
    : type_{_type},
      left_coefficient_{_left_coefficient},
      right_coefficient_{_right_coefficient},
      left_saturation_{_left_saturation},
      right_saturation_{_right_saturation},
      deadband_center_{_deadband_center},
      deadband_size_{_deadband_size}
{
}

sge::input::joypad::ff::condition_type sge::input::joypad::ff::condition::type() const
{
  return type_;
}

sge::input::joypad::ff::left_coefficient sge::input::joypad::ff::condition::left_coefficient() const
{
  return left_coefficient_;
}

sge::input::joypad::ff::right_coefficient
sge::input::joypad::ff::condition::right_coefficient() const
{
  return right_coefficient_;
}

sge::input::joypad::ff::left_saturation sge::input::joypad::ff::condition::left_saturation() const
{
  return left_saturation_;
}

sge::input::joypad::ff::right_saturation sge::input::joypad::ff::condition::right_saturation() const
{
  return right_saturation_;
}

sge::input::joypad::ff::deadband_center sge::input::joypad::ff::condition::deadband_center() const
{
  return deadband_center_;
}

sge::input::joypad::ff::deadband_size sge::input::joypad::ff::condition::deadband_size() const
{
  return deadband_size_;
}
