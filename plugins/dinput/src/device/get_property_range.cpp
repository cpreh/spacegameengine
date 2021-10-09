//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/get_property.hpp>
#include <sge/dinput/device/get_property_range.hpp>
#include <sge/dinput/device/range.hpp>
#include <fcppt/cast/size.hpp>

sge::dinput::device::range const sge::dinput::device::get_property_range(
    IDirectInputDevice8 &_device, DIDEVICEOBJECTINSTANCE const &_data, REFGUID _guid)
{
  DIPROPRANGE result;

  result.diph.dwSize = fcppt::cast::size<DWORD>(sizeof(DIPROPRANGE));

  sge::dinput::device::get_property(_device, _data, _guid, result.diph);

  return sge::dinput::device::range(result.lMin, result.lMax);
}
