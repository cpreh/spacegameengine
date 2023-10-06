//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/fog_mode.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/fog/mode.hpp>
#include <fcppt/assert/unreachable.hpp>

GLint sge::opengl::state::convert::fog_mode(sge::renderer::state::ffp::fog::mode const _mode)
{
  switch (_mode)
  {
  case sge::renderer::state::ffp::fog::mode::linear:
    return GL_LINEAR;
  case sge::renderer::state::ffp::fog::mode::exp:
    return GL_EXP;
  case sge::renderer::state::ffp::fog::mode::exp2:
    return GL_EXP2;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
