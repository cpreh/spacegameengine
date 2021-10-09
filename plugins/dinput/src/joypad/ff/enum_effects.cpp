//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/enum_effects.hpp>
#include <sge/dinput/joypad/ff/guid_to_type.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/ff/type_field.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/maybe_void.hpp>

namespace
{

BOOL callback(LPCDIEFFECTINFO, LPVOID);

}

sge::input::joypad::ff::type_field
sge::dinput::joypad::ff::enum_effects(IDirectInputDevice8 &_device)
{
  sge::input::joypad::ff::type_field data(sge::input::joypad::ff::type_field::null());

  if (_device.EnumEffects(callback, &data, DIEFT_ALL) != DI_OK)
    throw sge::input::exception{FCPPT_TEXT("EnumEffects failed")};

  return data;
}

namespace
{

BOOL callback(LPCDIEFFECTINFO const _info, LPVOID const _data)
{
  sge::input::joypad::ff::type_field &data(
      *fcppt::cast::from_void_ptr<sge::input::joypad::ff::type_field *>(_data));

  fcppt::optional::maybe_void(
      sge::dinput::joypad::ff::guid_to_type(_info->guid),
      [&data](sge::input::joypad::ff::type const _type) { data |= _type; });

  return DIENUM_CONTINUE;
}

}
