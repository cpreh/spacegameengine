//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/impl/convert_cursor_button.hpp>
#include <sge/cegui/impl/optional_mouse_button.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/InputEvent.h>
#include <fcppt/config/external_end.hpp>

sge::cegui::impl::optional_mouse_button
sge::cegui::impl::convert_cursor_button(sge::input::cursor::button_code const _code)
{
  switch (_code)
  {
  case sge::input::cursor::button_code::left:
    return sge::cegui::impl::optional_mouse_button{CEGUI::LeftButton};
  case sge::input::cursor::button_code::right:
    return sge::cegui::impl::optional_mouse_button{CEGUI::RightButton};
  case sge::input::cursor::button_code::middle:
    return sge::cegui::impl::optional_mouse_button{CEGUI::MiddleButton};
  case sge::input::cursor::button_code::unknown:
    return sge::cegui::impl::optional_mouse_button{CEGUI::NoButton};
  }

  FCPPT_ASSERT_UNREACHABLE;
}
