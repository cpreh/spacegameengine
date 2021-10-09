//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/cast_key.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/mouse/button_code.hpp>
#include <sge/input/mouse/button_code.hpp>

sge::input::mouse::button_code sge::dinput::mouse::button_code(DWORD const _code)
{
  if (_code == dinput::cast_key(DIMOFS_BUTTON0))
    return sge::input::mouse::button_code::left;
  else if (_code == dinput::cast_key(DIMOFS_BUTTON1))
    return sge::input::mouse::button_code::right;
  else if (_code == dinput::cast_key(DIMOFS_BUTTON2))
    return sge::input::mouse::button_code::middle;

  return sge::input::mouse::button_code::unknown;
}
