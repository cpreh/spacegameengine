//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/opengl/state/ffp/lighting/light/color.hpp>
#include <sge/opengl/state/ffp/lighting/light/directional.hpp>
#include <sge/opengl/state/ffp/lighting/light/make_actors.hpp>
#include <sge/opengl/state/ffp/lighting/light/point.hpp>
#include <sge/opengl/state/ffp/lighting/light/spot.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/match.hpp>

sge::opengl::state::index_actor_vector sge::opengl::state::ffp::lighting::light::make_actors(
    sge::renderer::state::ffp::lighting::light::parameters const &_parameters)
{
  return fcppt::container::join(
      sge::opengl::state::index_actor_vector{
          sge::opengl::state::ffp::lighting::light::color(GL_AMBIENT, _parameters.ambient().get()),
          sge::opengl::state::ffp::lighting::light::color(GL_DIFFUSE, _parameters.diffuse().get()),
          sge::opengl::state::ffp::lighting::light::color(
              GL_SPECULAR, _parameters.specular().get())},
      fcppt::variant::match(
          _parameters.variant(),
          &sge::opengl::state::ffp::lighting::light::directional,
          &sge::opengl::state::ffp::lighting::light::point,
          &sge::opengl::state::ffp::lighting::light::spot));
}
