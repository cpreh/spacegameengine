//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/sdl/get_window_display_mode.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>

fcppt::optional::object<SDL_DisplayMode>
sge::opengl::sdl::get_window_display_mode(awl::backends::sdl::window::object &_window)
{
  SDL_DisplayMode result{};

  return fcppt::optional::make_if(
      SDL_GetWindowDisplayMode(&_window.get().get(), &result) == 0, [&result] { return result; });
}
