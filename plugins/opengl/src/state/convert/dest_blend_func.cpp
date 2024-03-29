//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/dest_blend_func.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum
sge::opengl::state::convert::dest_blend_func(sge::renderer::state::core::blend::dest const _func)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_func)
  {
  case sge::renderer::state::core::blend::dest::zero:
    return GL_ZERO;
  case sge::renderer::state::core::blend::dest::one:
    return GL_ONE;
  case sge::renderer::state::core::blend::dest::src_color:
    return GL_SRC_COLOR;
  case sge::renderer::state::core::blend::dest::inv_src_color:
    return GL_ONE_MINUS_SRC_COLOR;
  case sge::renderer::state::core::blend::dest::src_alpha:
    return GL_SRC_ALPHA;
  case sge::renderer::state::core::blend::dest::inv_src_alpha:
    return GL_ONE_MINUS_SRC_ALPHA;
  case sge::renderer::state::core::blend::dest::dest_alpha:
    return GL_DST_ALPHA;
  case sge::renderer::state::core::blend::dest::inv_dest_alpha:
    return GL_ONE_MINUS_DST_ALPHA;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_func);
}
