//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_VOLUME_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_VOLUME_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/color_volume_types_fwd.hpp>
#include <sge/opengl/texture/volume_types_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/texture/volume_fwd.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <fcppt/string.hpp>

namespace sge::opengl::texture
{

struct volume_types
{
  using base = sge::renderer::texture::volume;

  using parameters = sge::renderer::texture::volume_parameters;

  using buffer_types = sge::opengl::texture::color_volume_types;

  [[nodiscard]] static fcppt::string name();
};

}

#endif
