//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/get_property.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>

void sge::dinput::device::get_property(
    IDirectInputDevice8 &_device,
    DIDEVICEOBJECTINSTANCE const &_data,
    REFGUID _guid,
    DIPROPHEADER &_result)
{
  _result.dwHeaderSize = fcppt::cast::size<DWORD>(sizeof(DIPROPHEADER));

  _result.dwHow = DIPH_BYOFFSET;

  _result.dwObj = _data.dwOfs;

  switch (_device.GetProperty(_guid, &_result))
  {
  case DI_OK:
  case S_FALSE:
    break;
  default:
    throw sge::input::exception(FCPPT_TEXT("GetProperty failed!"));
  }
}
