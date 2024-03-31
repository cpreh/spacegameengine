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
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
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
        sge::input::joypad::ff::waveform const waveform{_periodic.waveform()};

        FCPPT_PP_PUSH_WARNING
        FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
        switch (waveform)
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
        FCPPT_PP_POP_WARNING

        throw fcppt::enum_::make_invalid(waveform);
      },
      [](sge::input::joypad::ff::condition const &_condition) -> REFGUID
      {
        sge::input::joypad::ff::condition_type const type{_condition.type()};

        FCPPT_PP_PUSH_WARNING
        FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
        switch(type)
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
        FCPPT_PP_POP_WARNING

        throw fcppt::enum_::make_invalid(type);
      });
}
