//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/ds/format.hpp>
#include <sge/opengl/convert/depth_stencil_to_internal_format.hpp>
#include <sge/opengl/fbo/const_config_ref.hpp>
#include <sge/opengl/fbo/depth_stencil_surface.hpp>
#include <sge/opengl/fbo/render_buffer.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters.hpp>

sge::opengl::fbo::depth_stencil_surface::depth_stencil_surface(
    sge::opengl::fbo::const_config_ref const _context,
    sge::renderer::depth_stencil_buffer::surface_parameters const &_parameters)
    : sge::renderer::depth_stencil_buffer::surface(),
      render_buffer_(
          _context,
          sge::opengl::convert::depth_stencil_to_internal_format(_parameters.format()),
          _parameters.size()),
      dim_(_parameters.size()),
      format_(_parameters.format())
{
}

sge::opengl::fbo::depth_stencil_surface::~depth_stencil_surface() = default;

sge::opengl::fbo::render_buffer const &
sge::opengl::fbo::depth_stencil_surface::render_buffer() const
{
  return render_buffer_;
}

sge::opengl::fbo::depth_stencil_surface::dim sge::opengl::fbo::depth_stencil_surface::size() const
{
  return dim_;
}

sge::image::ds::format sge::opengl::fbo::depth_stencil_surface::format() const { return format_; }
