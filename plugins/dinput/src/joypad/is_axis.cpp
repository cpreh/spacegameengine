//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/is_axis.hpp>

bool sge::dinput::joypad::is_axis(GUID const _guid)
{
  return _guid == GUID_XAxis || _guid == GUID_YAxis || _guid == GUID_ZAxis ||
         _guid == GUID_RxAxis || _guid == GUID_RyAxis || _guid == GUID_RzAxis ||
         _guid == GUID_Slider;
}
