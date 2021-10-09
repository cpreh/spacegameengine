//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_FBO_DEPTH_STENCIL_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_FBO_DEPTH_STENCIL_SURFACE_HPP_INCLUDED

#include <sge/image/ds/format.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/const_config_ref.hpp>
#include <sge/opengl/fbo/depth_stencil_surface_fwd.hpp>
#include <sge/opengl/fbo/render_buffer.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::fbo
{

class depth_stencil_surface : public sge::renderer::depth_stencil_buffer::surface
{
  FCPPT_NONMOVABLE(depth_stencil_surface);

public:
  depth_stencil_surface(
      sge::opengl::fbo::const_config_ref,
      sge::renderer::depth_stencil_buffer::surface_parameters const &);

  ~depth_stencil_surface() override;

  [[nodiscard]] sge::opengl::fbo::render_buffer const &render_buffer() const;

private:
  [[nodiscard]] dim size() const override;

  [[nodiscard]] sge::image::ds::format format() const override;

  sge::opengl::fbo::render_buffer const render_buffer_;

  dim const dim_;

  sge::image::ds::format const format_;
};

}

#endif
