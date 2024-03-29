//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/fog_mode.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/fog/mode.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLint sge::opengl::state::convert::fog_mode(sge::renderer::state::ffp::fog::mode const _mode)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_mode)
  {
  case sge::renderer::state::ffp::fog::mode::linear:
    return GL_LINEAR;
  case sge::renderer::state::ffp::fog::mode::exp:
    return GL_EXP;
  case sge::renderer::state::ffp::fog::mode::exp2:
    return GL_EXP2;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_mode);
}
