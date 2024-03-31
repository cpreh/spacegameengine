//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/sdlinput/translate/pressed_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

bool sge::sdlinput::translate::pressed_impl(std::uint8_t const _state)
{
  switch (_state)
  {
  case SDL_PRESSED:
    return true;
  case SDL_RELEASED:
    return false;
  default:
    break;
  }

  throw sge::input::exception{FCPPT_TEXT("Invalid pressed state in sdlinput!")};
}
