//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/create_device.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/dinput_device_unique_ptr.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>

sge::dinput::dinput_device_unique_ptr
sge::dinput::create_device(IDirectInput8 &_dinput, GUID const _guid)
{
  IDirectInputDevice8 *ret;

  if (_dinput.CreateDevice(_guid, &ret, NULL) != DI_OK)
    throw sge::input::exception(FCPPT_TEXT("CreateDevice() failed!"));

  return sge::dinput::dinput_device_unique_ptr(ret);
}
