//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/ffp/lighting/light/cutoff_angle.hpp>
#include <sge/opengl/state/ffp/lighting/light/float.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/lighting/light/cutoff_angle.hpp>

sge::opengl::state::index_actor sge::opengl::state::ffp::lighting::light::cutoff_angle(
    sge::renderer::state::ffp::lighting::light::cutoff_angle const _angle)
{
  return sge::opengl::state::ffp::lighting::light::float_(GL_SPOT_CUTOFF, _angle.get());
}
