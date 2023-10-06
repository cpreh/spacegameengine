//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/core/blend/alpha.hpp>
#include <sge/opengl/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled_fwd.hpp>
#include <sge/renderer/state/core/blend/alpha_off_fwd.hpp>
#include <sge/renderer/state/core/blend/alpha_variant.hpp>
#include <fcppt/variant/match.hpp>

sge::opengl::state::actor_vector sge::opengl::state::core::blend::alpha(
    sge::opengl::context::object_ref const _context,
    sge::renderer::state::core::blend::alpha_variant const &_variant)
{
  return fcppt::variant::match(
      _variant,
      [](sge::renderer::state::core::blend::alpha_off const &)
      {
        return sge::opengl::state::actor_vector{
            sge::opengl::state::actor{[] { sge::opengl::disable(GL_BLEND); }}};
      },
      [_context](sge::renderer::state::core::blend::alpha_enabled const &_enabled)
      {
        return sge::opengl::state::actor_vector{
            sge::opengl::state::actor{[] { sge::opengl::enable(GL_BLEND); }},
            sge::opengl::state::core::blend::alpha_enabled(_context, _enabled)};
      });
}
