//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/read_bits.hpp>
#include <sge/evdev/device/read_bits_result.hpp>
#include <sge/evdev/joypad/ff/make_info.hpp>
#include <sge/input/joypad/ff/type.hpp>
#include <sge/input/joypad/ff/type_field.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/int_to_enum.hpp>
#include <fcppt/container/bitfield/init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>

namespace
{

sge::evdev::device::event_type_value to_linux_effect(sge::input::joypad::ff::type const _type)
{
  switch (_type)
  {
  case sge::input::joypad::ff::type::constant:
    return FF_CONSTANT;
  case sge::input::joypad::ff::type::spring:
    return FF_SPRING;
  case sge::input::joypad::ff::type::friction:
    return FF_FRICTION;
  case sge::input::joypad::ff::type::damper:
    return FF_DAMPER;
  case sge::input::joypad::ff::type::inertia:
    return FF_INERTIA;
  case sge::input::joypad::ff::type::ramp:
    return FF_RAMP;
  case sge::input::joypad::ff::type::square:
    return FF_SQUARE;
  case sge::input::joypad::ff::type::sine:
    return FF_SINE;
  case sge::input::joypad::ff::type::saw_up:
    return FF_SAW_UP;
  case sge::input::joypad::ff::type::saw_down:
    return FF_SAW_DOWN;
  case sge::input::joypad::ff::type::custom:
    return FF_CUSTOM;
  }

  FCPPT_ASSERT_UNREACHABLE;
}

enum class ff_type
{
  fcppt_maximum = FF_MAX
};

}

sge::input::joypad::ff::type_field sge::evdev::joypad::ff::make_info(sge::evdev::device::fd &_fd)
{
  sge::evdev::device::read_bits_result<ff_type> const result(
      sge::evdev::device::read_bits<ff_type>(_fd, EV_FF));

  return fcppt::container::bitfield::init<sge::input::joypad::ff::type_field>(
      [&result](sge::input::joypad::ff::type const _value)
      { return result.get(fcppt::cast::int_to_enum<ff_type>(to_linux_effect(_value))); });
}
