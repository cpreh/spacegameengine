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
#include <sge/opengl/state/convert/alpha_func.hpp>
#include <sge/opengl/state/ffp/alpha_test/make_actors.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/alpha_test/enabled.hpp>
#include <sge/renderer/state/ffp/alpha_test/off_fwd.hpp>
#include <sge/renderer/state/ffp/alpha_test/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/match.hpp>

sge::opengl::state::actor_vector sge::opengl::state::ffp::alpha_test::make_actors(
    sge::renderer::state::ffp::alpha_test::parameters const &_parameters)
{
  return fcppt::variant::match(
      _parameters.variant(),
      [](sge::renderer::state::ffp::alpha_test::off const &)
      {
        return sge::opengl::state::actor_vector{
            sge::opengl::state::actor{[] { sge::opengl::disable(GL_ALPHA_TEST); }}};
      },
      [](sge::renderer::state::ffp::alpha_test::enabled const &_enabled)
      {
        return sge::opengl::state::actor_vector{
            sge::opengl::state::actor{[] { sge::opengl::enable(GL_ALPHA_TEST); }},
            sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
                [_enabled]
                {
                  sge::opengl::call(
                      ::glAlphaFunc,
                      sge::opengl::state::convert::alpha_func(_enabled.func()),
                      _enabled.ref().get());
                },
                FCPPT_TEXT("glAlphaFunc"))};
      });
}
