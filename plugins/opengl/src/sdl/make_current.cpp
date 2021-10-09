//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/sdl/make_current.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>

void sge::opengl::sdl::make_current(
    awl::backends::sdl::window::object &_window,
    SDL_GLContext const _context // NOLINT(misc-misplaced-const)
)
{
  if (SDL_GL_MakeCurrent(&_window.get().get(), _context) != 0)
  {
    throw sge::renderer::exception{FCPPT_TEXT("SDL_GL_MakeCurrent failed")};
  }
}
