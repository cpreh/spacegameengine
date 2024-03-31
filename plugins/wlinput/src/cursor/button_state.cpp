//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/wlinput/cursor/button_state.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::button_pressed sge::wlinput::cursor::button_state(std::uint32_t const _state)
{
  switch (_state)
  {
  case WL_POINTER_BUTTON_STATE_RELEASED:
    return sge::input::cursor::button_pressed{false};
  case WL_POINTER_BUTTON_STATE_PRESSED:
    return sge::input::cursor::button_pressed{true};
  default:
    break;
  }

  throw sge::input::exception{FCPPT_TEXT("Invalid cursor button state in wlinput!")};
}
