//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_COLOR_SURFACE_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_COLOR_SURFACE_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/basic_lockable_buffer_fwd.hpp>
#include <sge/opengl/texture/buffer_surface_types_fwd.hpp>
#include <sge/opengl/texture/color_format_types_fwd.hpp>
#include <sge/opengl/texture/color_surface_types_fwd.hpp>
#include <sge/renderer/color_buffer/writable_surface_fwd.hpp>

namespace sge::opengl::texture
{

struct color_surface_types
{
  using base = sge::renderer::color_buffer::writable_surface;

  // TODO(philipp): Factor this out!
  using gl_buffer =
      sge::opengl::texture::basic_lockable_buffer<sge::opengl::texture::color_surface_types>;

  using dim_types = sge::opengl::texture::buffer_surface_types;

  using format_types = sge::opengl::texture::color_format_types;
};

}

#endif
