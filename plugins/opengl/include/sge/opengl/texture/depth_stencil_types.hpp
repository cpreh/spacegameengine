//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/depth_stencil_surface_types_fwd.hpp>
#include <sge/opengl/texture/depth_stencil_types_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <fcppt/string.hpp>

namespace sge::opengl::texture
{

struct depth_stencil_types
{
  using base = sge::renderer::texture::depth_stencil;

  using parameters = sge::renderer::texture::depth_stencil_parameters;

  using buffer_types = sge::opengl::texture::depth_stencil_surface_types;

  [[nodiscard]] static fcppt::string name();
};

}

#endif
