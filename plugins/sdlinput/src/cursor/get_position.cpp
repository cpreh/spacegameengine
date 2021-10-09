//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/position.hpp>
#include <sge/sdlinput/cursor/get_position.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_mouse.h>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::position sge::sdlinput::cursor::get_position()
{
  int x{0};
  int y{0};

  SDL_GetMouseState(&x, &y);

  return sge::input::cursor::position{x, y};
}
