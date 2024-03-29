//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/stencil_op.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/config.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/op_separate.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/depth_fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/pass_op.hpp>
#include <fcppt/text.hpp>

sge::opengl::state::actor sge::opengl::state::core::depth_stencil::stencil::op_separate(
    sge::opengl::state::core::depth_stencil::stencil::config const &_config,
    GLenum const _side,
    sge::renderer::state::core::depth_stencil::stencil::fail_op const _fail_op,
    sge::renderer::state::core::depth_stencil::stencil::depth_fail_op const _depth_fail_op,
    sge::renderer::state::core::depth_stencil::stencil::pass_op const _pass_op)
{
  return sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
      [&_config, _side, _fail_op, _depth_fail_op, _pass_op]
      {
        sge::opengl::call_fun_ref(
            _config.stencil_op_separate(),
            _side,
            sge::opengl::state::convert::stencil_op(_fail_op.get()),
            sge::opengl::state::convert::stencil_op(_depth_fail_op.get()),
            sge::opengl::state::convert::stencil_op(_pass_op.get()));
      },
      FCPPT_TEXT("glStencilOpSeparate"));
}
