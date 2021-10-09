//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/ffp/lighting/light/direction.hpp>
#include <sge/opengl/state/ffp/lighting/light/float_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/direction.hpp>

sge::opengl::state::index_actor sge::opengl::state::ffp::lighting::light::direction(
    sge::renderer::state::ffp::lighting::light::direction const &_direction)
{
  return sge::opengl::state::ffp::lighting::light::float_ptr(
      GL_SPOT_DIRECTION, _direction.get().storage().data());
}
