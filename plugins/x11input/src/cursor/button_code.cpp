//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/button_code.hpp>
#include <sge/x11input/cursor/button_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::button_code sge::x11input::cursor::button_code(int const _detail)
{
  switch (_detail)
  {
  case Button1:
    return sge::input::cursor::button_code::left;
  case Button2:
    return sge::input::cursor::button_code::middle;
  case Button3:
    return sge::input::cursor::button_code::right;
  default:
    break;
  }

  return sge::input::cursor::button_code::unknown;
}
