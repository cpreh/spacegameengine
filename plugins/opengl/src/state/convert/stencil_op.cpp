//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/stencil_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/op.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum sge::opengl::state::convert::stencil_op(
    sge::renderer::state::core::depth_stencil::stencil::op const _value)
{
  switch (_value)
  {
  case sge::renderer::state::core::depth_stencil::stencil::op::keep:
    return GL_KEEP;
  case sge::renderer::state::core::depth_stencil::stencil::op::zero:
    return GL_ZERO;
  case sge::renderer::state::core::depth_stencil::stencil::op::replace:
    return GL_REPLACE;
  case sge::renderer::state::core::depth_stencil::stencil::op::inc_sat:
    return GL_INCR;
  case sge::renderer::state::core::depth_stencil::stencil::op::inc_wrap:
    return GL_INCR_WRAP;
  case sge::renderer::state::core::depth_stencil::stencil::op::dec_sat:
    return GL_DECR;
  case sge::renderer::state::core::depth_stencil::stencil::op::dec_wrap:
    return GL_DECR_WRAP;
  case sge::renderer::state::core::depth_stencil::stencil::op::invert:
    return GL_INVERT;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
