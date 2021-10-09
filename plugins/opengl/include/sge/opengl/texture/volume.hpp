//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_VOLUME_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_VOLUME_HPP_INCLUDED

#include <sge/opengl/texture/basic_box.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/buffer_volume_types.hpp>
#include <sge/opengl/texture/color_volume_types.hpp>
#include <sge/opengl/texture/volume_basic.hpp>
#include <sge/opengl/texture/volume_config_fwd.hpp>
#include <sge/opengl/texture/volume_types.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::texture
{

class volume : public sge::opengl::texture::volume_basic
{
  FCPPT_NONMOVABLE(volume);

public:
  volume(
      sge::opengl::texture::volume_config const &,
      sge::opengl::texture::basic_parameters const &,
      sge::renderer::texture::volume_parameters const &);

  ~volume() override;
};

}

#endif
