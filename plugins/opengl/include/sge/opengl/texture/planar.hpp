//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_PLANAR_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_PLANAR_HPP_INCLUDED

#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/planar_basic.hpp>
#include <sge/opengl/texture/planar_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::texture
{

class planar : public sge::opengl::texture::planar_basic
{
  FCPPT_NONMOVABLE(planar);

public:
  planar(
      sge::opengl::texture::basic_parameters const &,
      sge::renderer::texture::planar_parameters const &);

  ~planar() override;
};

}

#endif
