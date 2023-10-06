//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/ds/format.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/ext.hpp>
#include <sge/opengl/convert/depth_stencil_order.hpp>
#include <sge/opengl/convert/make_color_order.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::opengl::color_order
sge::opengl::convert::depth_stencil_order(sge::image::ds::format const _format)
{
  switch (_format)
  {
  case sge::image::ds::format::d16:
  case sge::image::ds::format::d32:
    return sge::opengl::convert::make_color_order<GL_DEPTH_COMPONENT>();
  case sge::image::ds::format::d24s8:
    return sge::opengl::convert::make_color_order<GL_DEPTH_STENCIL>();
  }

  FCPPT_ASSERT_UNREACHABLE;
}
