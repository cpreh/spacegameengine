//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/scroll_code.hpp>
#include <sge/x11input/cursor/scroll_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::scroll_code sge::x11input::cursor::scroll_code(int const _scroll_type)
{
  switch (_scroll_type)
  {
  case XIScrollTypeVertical:
    return sge::input::cursor::scroll_code::vertical;
  case XIScrollTypeHorizontal:
    return sge::input::cursor::scroll_code::horizontal;
  default:
    break;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
