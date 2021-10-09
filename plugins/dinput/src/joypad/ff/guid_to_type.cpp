//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/guid_to_type.hpp>
#include <sge/dinput/joypad/ff/optional_type.hpp>
#include <sge/input/joypad/ff/type.hpp>

sge::dinput::joypad::ff::optional_type sge::dinput::joypad::ff::guid_to_type(REFGUID _guid)
{
  if (_guid == GUID_ConstantForce)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::constant};

  if (_guid == GUID_Spring)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::spring};

  if (_guid == GUID_Friction)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::friction};

  if (_guid == GUID_Damper)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::damper};

  if (_guid == GUID_Inertia)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::inertia};

  if (_guid == GUID_RampForce)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::ramp};

  if (_guid == GUID_Square)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::square};

  if (_guid == GUID_Sine)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::sine};

  if (_guid == GUID_SawtoothUp)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::saw_up};

  if (_guid == GUID_SawtoothDown)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::saw_down};

  if (_guid == GUID_CustomForce)
    return sge::dinput::joypad::ff::optional_type{sge::input::joypad::ff::type::custom};

  return sge::dinput::joypad::ff::optional_type{};
}
