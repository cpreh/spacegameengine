//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/variant_to_guid.hpp>
#include <sge/input/joypad/ff/condition.hpp>
#include <sge/input/joypad/ff/condition_type.hpp>
#include <sge/input/joypad/ff/constant_fwd.hpp>
#include <sge/input/joypad/ff/periodic.hpp>
#include <sge/input/joypad/ff/ramp_fwd.hpp>
#include <sge/input/joypad/ff/variant.hpp>
#include <sge/input/joypad/ff/waveform.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/variant/match.hpp>

REFGUID
sge::dinput::joypad::ff::variant_to_guid(sge::input::joypad::ff::variant const &_variant)
{
  return fcppt::variant::match(
      _variant,
      [](sge::input::joypad::ff::constant const &) -> REFGUID { return GUID_ConstantForce; },
      [](sge::input::joypad::ff::ramp const &) -> REFGUID { return GUID_RampForce; },
      [](sge::input::joypad::ff::periodic const &_periodic) -> REFGUID
      {
        switch (_periodic.waveform())
        {
        case sge::input::joypad::ff::waveform::square:
          return GUID_Square;
        case sge::input::joypad::ff::waveform::triangle:
          return GUID_Triangle;
        case sge::input::joypad::ff::waveform::sine:
          return GUID_Sine;
        case sge::input::joypad::ff::waveform::saw_up:
          return GUID_SawtoothUp;
        case sge::input::joypad::ff::waveform::saw_down:
          return GUID_SawtoothDown;
        }

        FCPPT_ASSERT_UNREACHABLE;
      },
      [](sge::input::joypad::ff::condition const &_condition) -> REFGUID
      {
        switch (_condition.type())
        {
        case sge::input::joypad::ff::condition_type::spring:
          return GUID_Spring;
        case sge::input::joypad::ff::condition_type::damper:
          return GUID_Damper;
        case sge::input::joypad::ff::condition_type::inertia:
          return GUID_Inertia;
        case sge::input::joypad::ff::condition_type::friction:
          return GUID_Friction;
        }

        FCPPT_ASSERT_UNREACHABLE;
      });
}
