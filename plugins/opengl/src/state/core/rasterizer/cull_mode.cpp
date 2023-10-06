//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/cull_mode.hpp>
#include <sge/opengl/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <fcppt/text.hpp>

sge::opengl::state::actor_vector sge::opengl::state::core::rasterizer::cull_mode(
    sge::renderer::state::core::rasterizer::cull_mode const _mode)
{
  return _mode == sge::renderer::state::core::rasterizer::cull_mode::off
             ? sge::opengl::state::actor_vector{sge::opengl::state::actor{
                   [] { return sge::opengl::disable(GL_CULL_FACE); }}}
             : sge::opengl::state::actor_vector{
                   sge::opengl::state::actor{[] { return sge::opengl::enable(GL_CULL_FACE); }},
                   sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
                       [_mode] {
                         return sge::opengl::call(
                             ::glCullFace, sge::opengl::state::convert::cull_mode(_mode));
                       },
                       FCPPT_TEXT("glCullFace"))};
}
