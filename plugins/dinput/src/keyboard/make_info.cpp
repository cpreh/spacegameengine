//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerate_objects.hpp>
#include <sge/dinput/keyboard/enumerator.hpp>
#include <sge/dinput/keyboard/info.hpp>
#include <sge/dinput/keyboard/make_info.hpp>

sge::dinput::keyboard::info sge::dinput::keyboard::make_info(IDirectInputDevice8 &_device)
{
  sge::dinput::keyboard::enumerator object;

  sge::dinput::device::enumerate_objects(_device, object, DIDFT_ALL);

  return sge::dinput::keyboard::info(object.key_map());
}
