//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/stencil_func.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum sge::opengl::state::convert::stencil_func(
    sge::renderer::state::core::depth_stencil::stencil::func const _func)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_func)
  {
  case sge::renderer::state::core::depth_stencil::stencil::func::never:
    return GL_NEVER;
  case sge::renderer::state::core::depth_stencil::stencil::func::less:
    return GL_LESS;
  case sge::renderer::state::core::depth_stencil::stencil::func::equal:
    return GL_EQUAL;
  case sge::renderer::state::core::depth_stencil::stencil::func::less_equal:
    return GL_LEQUAL;
  case sge::renderer::state::core::depth_stencil::stencil::func::greater:
    return GL_GREATER;
  case sge::renderer::state::core::depth_stencil::stencil::func::not_equal:
    return GL_NOTEQUAL;
  case sge::renderer::state::core::depth_stencil::stencil::func::greater_equal:
    return GL_GEQUAL;
  case sge::renderer::state::core::depth_stencil::stencil::func::always:
    return GL_ALWAYS;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_func);
}
