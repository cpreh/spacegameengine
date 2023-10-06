//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/lighting/light/float_ptr.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>

sge::opengl::state::index_actor
sge::opengl::state::ffp::lighting::light::float_ptr(GLenum const _name, GLfloat const *const _value)
{
  return sge::opengl::state::wrap_error_handler<sge::opengl::state::index_actor>(
      [_name, _value](GLenum const _index)
      { sge::opengl::call(::glLightfv, _index, _name, _value); },
      FCPPT_TEXT("glLightfv"));
}
