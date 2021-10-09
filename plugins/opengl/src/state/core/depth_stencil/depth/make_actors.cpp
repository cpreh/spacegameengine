//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/depth_func.hpp>
#include <sge/opengl/state/core/depth_stencil/depth/make_actors.hpp>
#include <sge/opengl/state/core/depth_stencil/depth/write_enable.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/off_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/variant.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/write_enable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/match.hpp>

sge::opengl::state::actor_vector sge::opengl::state::core::depth_stencil::depth::make_actors(
    sge::renderer::state::core::depth_stencil::depth::variant const &_variant)
{
  return fcppt::variant::match(
      _variant,
      [](sge::renderer::state::core::depth_stencil::depth::off const &)
      {
        return sge::opengl::state::actor_vector{
            sge::opengl::state::actor{[] { sge::opengl::disable(GL_DEPTH_TEST); }},
            sge::opengl::state::core::depth_stencil::depth::write_enable(
                sge::renderer::state::core::depth_stencil::depth::write_enable(true))};
      },
      [](sge::renderer::state::core::depth_stencil::depth::enabled const &_enabled)
      {
        return sge::opengl::state::actor_vector{
            sge::opengl::state::actor{[] { sge::opengl::enable(GL_DEPTH_TEST); }},
            sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
                [_enabled]
                {
                  return sge::opengl::call(
                      ::glDepthFunc, sge::opengl::state::convert::depth_func(_enabled.func()));
                },
                FCPPT_TEXT("glDepthFunc")),
            sge::opengl::state::core::depth_stencil::depth::write_enable(_enabled.write_enable())};
      });
}
