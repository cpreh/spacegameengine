//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/to_gl_bool.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/core/depth_stencil/depth/write_enable.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/write_enable.hpp>
#include <fcppt/text.hpp>

sge::opengl::state::actor sge::opengl::state::core::depth_stencil::depth::write_enable(
    sge::renderer::state::core::depth_stencil::depth::write_enable const _write_enable)
{
  return sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
      [_write_enable] {
        return sge::opengl::call(
            ::glDepthMask, sge::opengl::convert::to_gl_bool(_write_enable.get()));
      },
      FCPPT_TEXT("glDepthMask"));
}
