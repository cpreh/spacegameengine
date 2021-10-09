//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/scroll_code.hpp>
#include <sge/wlinput/cursor/scroll_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::scroll_code sge::wlinput::cursor::scroll_code(std::uint32_t const _code)
{
  switch (_code)
  {
  case WL_POINTER_AXIS_VERTICAL_SCROLL:
    return sge::input::cursor::scroll_code::vertical;
  case WL_POINTER_AXIS_HORIZONTAL_SCROLL:
    return sge::input::cursor::scroll_code::horizontal;
  default:
    break;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
