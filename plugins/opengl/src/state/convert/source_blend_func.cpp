//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/source_blend_func.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum sge::opengl::state::convert::source_blend_func(
    sge::renderer::state::core::blend::source const _func)
{
  switch (_func)
  {
  case sge::renderer::state::core::blend::source::zero:
    return GL_ZERO;
  case sge::renderer::state::core::blend::source::one:
    return GL_ONE;
  case sge::renderer::state::core::blend::source::dest_color:
    return GL_DST_COLOR;
  case sge::renderer::state::core::blend::source::inv_dest_color:
    return GL_ONE_MINUS_DST_COLOR;
  case sge::renderer::state::core::blend::source::src_alpha:
    return GL_SRC_ALPHA;
  case sge::renderer::state::core::blend::source::inv_src_alpha:
    return GL_ONE_MINUS_SRC_ALPHA;
  case sge::renderer::state::core::blend::source::dest_alpha:
    return GL_DST_ALPHA;
  case sge::renderer::state::core::blend::source::inv_dest_alpha:
    return GL_ONE_MINUS_DST_ALPHA;
  case sge::renderer::state::core::blend::source::src_alpha_sat:
    return GL_SRC_ALPHA_SATURATE;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
