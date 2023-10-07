//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/ds/format.hpp>
#include <sge/opengl/ext.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/convert/depth_stencil_to_internal_format.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::opengl::internal_color_format
sge::opengl::convert::depth_stencil_to_internal_format(sge::image::ds::format const _type)
{
  switch (_type)
  {
  case sge::image::ds::format::d16:
    return sge::opengl::internal_color_format(GL_DEPTH_COMPONENT16);
  case sge::image::ds::format::d32:
    return sge::opengl::internal_color_format(GL_DEPTH_COMPONENT32);
  case sge::image::ds::format::d24s8:
    return sge::opengl::internal_color_format(GL_DEPTH_COMPONENT24);
  }

  FCPPT_ASSERT_UNREACHABLE;
}
