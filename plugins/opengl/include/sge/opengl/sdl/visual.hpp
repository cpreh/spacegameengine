//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_SDL_VISUAL_HPP_INCLUDED
#define SGE_OPENGL_SDL_VISUAL_HPP_INCLUDED

#include <sge/renderer/pixel_format/object.hpp>
#include <awl/backends/sdl/visual/object.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::sdl
{

class visual : public awl::backends::sdl::visual::object
{
  FCPPT_NONMOVABLE(visual);

public:
  explicit visual(sge::renderer::pixel_format::object const &);

  ~visual() override;

  void apply() const override;

private:
  sge::renderer::pixel_format::object const pixel_format_;
};

}

#endif
