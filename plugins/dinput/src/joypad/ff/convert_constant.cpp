//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/convert_constant.hpp>
#include <sge/input/joypad/ff/constant.hpp>
#include <fcppt/cast/size.hpp>

DICONSTANTFORCE
sge::dinput::joypad::ff::convert_constant(sge::input::joypad::ff::constant const &_constant)
{
  return DICONSTANTFORCE{fcppt::cast::size<LONG>(_constant.magnitude().get())};
}
