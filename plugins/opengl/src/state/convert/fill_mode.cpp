//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/fill_mode.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum sge::opengl::state::convert::fill_mode(
    sge::renderer::state::core::rasterizer::fill_mode const _mode)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_mode)
  {
  case sge::renderer::state::core::rasterizer::fill_mode::line:
    return GL_LINE;
  case sge::renderer::state::core::rasterizer::fill_mode::solid:
    return GL_FILL;
  }

  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_mode);
}
