//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerate_objects.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>

namespace
{

BOOL CALLBACK dispatcher(LPCDIDEVICEOBJECTINSTANCE, LPVOID);

}

void sge::dinput::device::enumerate_objects(
    IDirectInputDevice8 &_device, sge::dinput::device::enumerator &_enumerator, DWORD const _flags)
{
  if (_device.EnumObjects(&dispatcher, static_cast<void *>(&_enumerator), _flags) != DI_OK)
    throw sge::input::exception{FCPPT_TEXT("enumerating objects failed!")};
}

namespace
{

BOOL CALLBACK dispatcher(LPCDIDEVICEOBJECTINSTANCE const _object, LPVOID const _ptr)
{
  fcppt::cast::from_void_ptr<sge::dinput::device::enumerator *>(_ptr)->dispatch(*_object);

  return DIENUM_CONTINUE;
}

}
