//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/funcs/unacquire.hpp>
#include <fcppt/assert/unreachable.hpp>

bool sge::dinput::device::funcs::unacquire(IDirectInputDevice8 &_device)
{
  switch (_device.Unacquire())
  {
  case DI_OK:
    return true;
  case DI_NOEFFECT:
    return false;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
