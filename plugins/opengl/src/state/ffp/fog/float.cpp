//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/fog/float.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>

sge::opengl::state::actor
sge::opengl::state::ffp::fog::float_(GLenum const _what, GLfloat const _value)
{
  return sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
      [_what, _value] { sge::opengl::call(::glFogf, _what, _value); }, FCPPT_TEXT("glFogf"));
}
