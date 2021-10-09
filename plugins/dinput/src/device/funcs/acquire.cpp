//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/funcs/acquire.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>

bool sge::dinput::device::funcs::acquire(IDirectInputDevice8 &_device)
{
  switch (_device.Acquire())
  {
  case S_FALSE:
  case DI_OK:
    return true;
  case DIERR_OTHERAPPHASPRIO:
    return false;
  default:
    throw sge::input::exception(FCPPT_TEXT("Acquire() failed!"));
  }
}
