//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/cast_key.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_code.hpp>

sge::input::mouse::axis_code sge::dinput::mouse::axis_code(DWORD const _code)
{
  if (_code == sge::dinput::cast_key(DIMOFS_X))
    return sge::input::mouse::axis_code::x;
  else if (_code == sge::dinput::cast_key(DIMOFS_Y))
    return sge::input::mouse::axis_code::y;
  else if (_code == sge::dinput::cast_key(DIMOFS_Z))
    return sge::input::mouse::axis_code::wheel;

  return sge::input::mouse::axis_code::unknown;
}
