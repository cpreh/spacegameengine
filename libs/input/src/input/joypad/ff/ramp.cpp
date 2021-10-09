//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/ff/end_magnitude.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <sge/input/joypad/ff/ramp.hpp>
#include <sge/input/joypad/ff/start_magnitude.hpp>

sge::input::joypad::ff::ramp::ramp(
    sge::input::joypad::ff::start_magnitude const _start_magnitude,
    sge::input::joypad::ff::end_magnitude const _end_magnitude,
    sge::input::joypad::ff::envelope const &_envelope)
    : start_magnitude_{_start_magnitude}, end_magnitude_{_end_magnitude}, envelope_{_envelope}
{
}

sge::input::joypad::ff::start_magnitude sge::input::joypad::ff::ramp::start_magnitude() const
{
  return start_magnitude_;
}

sge::input::joypad::ff::end_magnitude sge::input::joypad::ff::ramp::end_magnitude() const
{
  return end_magnitude_;
}

sge::input::joypad::ff::envelope const &sge::input::joypad::ff::ramp::envelope() const
{
  return envelope_;
}
