//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum sge::opengl::state::convert::cull_mode(
    sge::renderer::state::core::rasterizer::cull_mode const _mode)
{
  switch (_mode)
  {
  case sge::renderer::state::core::rasterizer::cull_mode::clockwise:
    return GL_BACK;
  case sge::renderer::state::core::rasterizer::cull_mode::counter_clockwise:
    return GL_FRONT;
  case sge::renderer::state::core::rasterizer::cull_mode::off:
    break;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
