//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/lighting/make_actors.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>
#include <sge/renderer/state/ffp/lighting/off_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/match.hpp>

sge::opengl::state::actor_vector sge::opengl::state::ffp::lighting::make_actors(
    sge::renderer::state::ffp::lighting::parameters const &_parameters)
{
  return fcppt::variant::match(
      _parameters.variant(),
      [](sge::renderer::state::ffp::lighting::off const &)
      {
        return sge::opengl::state::actor_vector{sge::opengl::state::actor{
            [] { return sge::opengl::disable(sge::opengl::convert::to_gl_enum<GL_LIGHTING>()); }}};
      },
      [](sge::renderer::state::ffp::lighting::enabled const &_enabled)
      {
        sge::image::color::rgba32f const ambient{
            sge::image::color::any::convert<sge::image::color::rgba32f_format>(
                _enabled.ambient_color().get())};

        return sge::opengl::state::actor_vector{
            sge::opengl::state::actor{[] {
              return sge::opengl::enable(sge::opengl::convert::to_gl_enum<GL_LIGHTING>());
            }},
            sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
                [ambient]
                {
                  sge::opengl::call(
                      ::glLightModelfv,
                      sge::opengl::convert::to_gl_enum<GL_LIGHT_MODEL_AMBIENT>(),
                      ambient.data());
                },
                FCPPT_TEXT("glLightModelfv")),
            sge::opengl::state::actor{[diffuse = _enabled.diffuse_from_vertex().get()] {
              sge::opengl::enable_bool(
                  sge::opengl::convert::to_gl_enum<GL_COLOR_MATERIAL>(), diffuse);
            }}};
      });
}
