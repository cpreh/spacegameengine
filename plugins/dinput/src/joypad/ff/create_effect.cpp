//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/create_effect.hpp>
#include <sge/dinput/joypad/ff/dinput_effect_unique_ptr.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>

sge::dinput::joypad::ff::dinput_effect_unique_ptr sge::dinput::joypad::ff::create_effect(
    IDirectInputDevice8 &_device, REFGUID _guid, DIEFFECT const &_effect)
{
  IDirectInputEffect *result;

  if (_device.CreateEffect(_guid, &_effect, &result, nullptr) != DI_OK)
    throw sge::input::exception{FCPPT_TEXT("CreateEffect failed")};

  return sge::dinput::joypad::ff::dinput_effect_unique_ptr{result};
}
