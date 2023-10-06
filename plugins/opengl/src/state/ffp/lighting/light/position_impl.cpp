//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/vector4f.hpp>
#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/ffp/lighting/light/float_ptr.hpp>
#include <sge/opengl/state/ffp/lighting/light/position_impl.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

sge::opengl::state::index_actor
sge::opengl::state::ffp::lighting::light::position_impl(sge::opengl::vector4f const &_pos4)
{
  return sge::opengl::state::ffp::lighting::light::float_ptr(GL_POSITION, _pos4.storage().data());
}
