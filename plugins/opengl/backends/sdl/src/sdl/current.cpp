//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/sdl/current.hpp>
#include <sge/opengl/sdl/make_current.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <awl/backends/sdl/window/object.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/sdl/window/object_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <string>
#include <fcppt/config/external_end.hpp>

sge::opengl::sdl::current::current(
    awl::backends::sdl::window::object_ref const _window,
    SDL_GLContext const _context // NOLINT(misc-misplaced-const)
    )
    : sge::opengl::backend::current{}, window_{_window}, context_{_context}
{
  sge::opengl::sdl::make_current(this->window_.get(), this->context_);
}

sge::opengl::sdl::current::~current()
{
  sge::opengl::sdl::make_current(this->window_.get(), nullptr);
}

sge::opengl::backend::fun_ptr
sge::opengl::sdl::current::load_function(std::string const &_function) const
{
  return
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      reinterpret_cast<sge::opengl::backend::fun_ptr>(SDL_GL_GetProcAddress(_function.c_str()));
}

void sge::opengl::sdl::current::begin_rendering() {}

void sge::opengl::sdl::current::end_rendering()
{
  SDL_GL_SwapWindow(&this->window_.get().get().get());
}

void sge::opengl::sdl::current::vsync(sge::renderer::display_mode::vsync const /*_vsync*/
)
{
  auto const convert_mode{
      [](sge::renderer::display_mode::vsync const _mode)
      {
        FCPPT_PP_PUSH_WARNING
        FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
        switch (_mode)
        {
        case sge::renderer::display_mode::vsync::on:
          return 1;
        case sge::renderer::display_mode::vsync::off:
          return 0;
        }
        FCPPT_PP_POP_WARNING

        throw fcppt::enum_::make_invalid(_mode);
      }};

  if (SDL_GL_SetSwapInterval(convert_mode(sge::renderer::display_mode::vsync::off
                                          //				_vsync
                                          )) != 0)
  {
    throw sge::renderer::exception{FCPPT_TEXT("SDL_GL_SetSwapInterval failed")};
  }
}
