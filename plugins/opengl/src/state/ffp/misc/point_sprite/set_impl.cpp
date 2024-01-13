//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/state/ffp/misc/point_sprite/const_config_ref.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set_impl.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set_texture.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/strong_typedef_arithmetic.hpp> // IWYU pragma: keep
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/type_iso/strong_typedef.hpp> // NOLINT(misc-include-cleaner)

sge::opengl::state::actor_vector sge::opengl::state::ffp::misc::point_sprite::set_impl(
    fcppt::log::object_reference const _log,
    sge::opengl::context::object_ref const _context,
    sge::opengl::state::ffp::misc::point_sprite::const_config_ref const _config,
    sge::renderer::state::ffp::misc::enable_point_sprites const _enable)
{
  return fcppt::container::join(
      sge::opengl::state::actor_vector{
          sge::opengl::state::actor{[flag = _config.get().point_sprite_flag(), _enable]
                                    { sge::opengl::enable_bool(flag.get(), _enable.get()); }},
          sge::opengl::state::actor{[flag = _config.get().vertex_shader_size_flag(), _enable]
                                    { sge::opengl::enable_bool(flag.get(), _enable.get()); }}},
      fcppt::algorithm::map<sge::opengl::state::actor_vector>(
          fcppt::make_int_range_count(fcppt::optional::maybe(
              sge::opengl::context::use<sge::opengl::texture::multi_context>(
                  _context, _context.get().info())
                  .config(),
              fcppt::const_(sge::renderer::texture::stage(1U)),
              [](sge::opengl::texture::multi_config const &_multi_config)
              { return sge::renderer::texture::stage(_multi_config.max_level().get()); })),
          [_log, _enable, _context, _config](sge::renderer::texture::stage const _stage)
          {
            return sge::opengl::state::actor{
                [_log, _context, _config, _stage, _enable]()
                {
                  sge::opengl::state::ffp::misc::point_sprite::set_texture(
                      _log.get(), _context.get(), _config.get(), _stage, _enable);
                }};
          }));
}
