//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED

#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/depth_stencil_basic.hpp>
#include <sge/opengl/texture/depth_stencil_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::texture
{

class depth_stencil : public sge::opengl::texture::depth_stencil_basic
{
  FCPPT_NONMOVABLE(depth_stencil);

public:
  depth_stencil(
      sge::opengl::texture::basic_parameters const &,
      sge::renderer::texture::depth_stencil_parameters const &);

  ~depth_stencil() override;
};

}

#endif
