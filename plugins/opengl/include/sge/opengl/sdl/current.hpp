//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_SDL_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_SDL_CURRENT_HPP_INCLUDED

#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/renderer/display_mode/vsync_fwd.hpp>
#include <awl/backends/sdl/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::sdl
{

class current : public sge::opengl::backend::current
{
  FCPPT_NONMOVABLE(current);

public:
  current(awl::backends::sdl::window::object_ref, SDL_GLContext);

  ~current() override;

  [[nodiscard]] sge::opengl::backend::fun_ptr load_function(std::string const &) const override;

  void begin_rendering() override;

  void end_rendering() override;

  void vsync(sge::renderer::display_mode::vsync) override;

private:
  awl::backends::sdl::window::object_ref const window_;

  SDL_GLContext const context_; // NOLINT(misc-misplaced-const)
};

}

#endif
