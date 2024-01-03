//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/ffp/sampler/context.hpp>
#include <sge/opengl/state/ffp/sampler/default_context.hpp>
#include <sge/opengl/state/ffp/sampler/object.hpp>
#include <sge/opengl/state/ffp/sampler/set_defaults.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_arithmetic.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>

void sge::opengl::state::ffp::sampler::set_defaults(
    fcppt::log::object &_log, sge::opengl::context::object &_context)
{
  // Samplers are always active in every stage and we must make sure that
  // the defaults are restored everywhere.

  fcppt::optional::maybe_void(
      sge::opengl::context::use<sge::opengl::texture::multi_context>(
          fcppt::make_ref(_context), _context.info())
          .config(),
      [&_log, &_context](sge::opengl::texture::multi_config const &_config)
      {
        sge::opengl::state::ffp::sampler::object const &default_state(
            sge::opengl::context::use<sge::opengl::state::ffp::sampler::default_context>(
                fcppt::make_ref(_context))
                .default_state());

        sge::opengl::context::use<sge::opengl::state::ffp::sampler::context>(
            fcppt::make_ref(_context))
            .stages(sge::renderer::texture::stage(0U));

        for (sge::renderer::texture::stage const stage :
             fcppt::make_int_range_count(sge::renderer::texture::stage{_config.max_level().get()}))
        {
          sge::opengl::texture::active_level const active_level(_log, _context, stage);

          default_state.set(active_level);
        }
      });
}
