//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config_fwd.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/context.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set_impl.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/maybe.hpp>

sge::opengl::state::actor_vector sge::opengl::state::ffp::misc::point_sprite::set(
    fcppt::log::object_reference const _log,
    sge::opengl::context::object_ref const _context,
    sge::renderer::state::ffp::misc::enable_point_sprites const _enable)
{
  return fcppt::optional::maybe(
      sge::opengl::context::use<sge::opengl::state::ffp::misc::point_sprite::context>(
          _context, _context.get().info())
          .config(),
      [_enable]
      {
        if (!_enable.get())
        {
          return sge::opengl::state::actor_vector();
        }

        throw sge::renderer::unsupported{
            FCPPT_TEXT("GL_POINT_SPRITE"),
            FCPPT_TEXT("opengl-2.0"),
            FCPPT_TEXT("ARB_point_sprite")};
      },
      [_log, _context, _enable](sge::opengl::state::ffp::misc::point_sprite::config const &_config)
      {
        return sge::opengl::state::ffp::misc::point_sprite::set_impl(
            _log, _context, fcppt::make_ref(_config), _enable);
      });
}
