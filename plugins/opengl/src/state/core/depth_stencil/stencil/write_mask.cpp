//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/write_mask.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>
#include <fcppt/text.hpp>

sge::opengl::state::actor sge::opengl::state::core::depth_stencil::stencil::write_mask(
    sge::renderer::state::core::depth_stencil::stencil::write_mask const _write_mask)
{
  return sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
      [_write_mask] { ::glStencilMask(static_cast<GLuint>(_write_mask.get())); },
      FCPPT_TEXT("glStencilMask"));
}
