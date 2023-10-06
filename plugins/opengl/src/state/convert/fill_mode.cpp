//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/fill_mode.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum sge::opengl::state::convert::fill_mode(
    sge::renderer::state::core::rasterizer::fill_mode const _mode)
{
  switch (_mode)
  {
  case sge::renderer::state::core::rasterizer::fill_mode::line:
    return GL_LINE;
  case sge::renderer::state::core::rasterizer::fill_mode::solid:
    return GL_FILL;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
