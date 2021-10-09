//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/convert_condition.hpp>
#include <sge/input/joypad/ff/condition.hpp>
#include <fcppt/cast/size.hpp>

DICONDITION
sge::dinput::joypad::ff::convert_condition(sge::input::joypad::ff::condition const &_condition)
{
  return DICONDITION{
      fcppt::cast::size<LONG>(_condition.deadband_center().get()),
      fcppt::cast::size<LONG>(_condition.right_coefficient().get()),
      fcppt::cast::size<LONG>(_condition.left_coefficient().get()),
      fcppt::cast::size<DWORD>(_condition.right_saturation().get()),
      fcppt::cast::size<DWORD>(_condition.left_saturation().get()),
      fcppt::cast::size<LONG>(_condition.deadband_size().get())};
}
