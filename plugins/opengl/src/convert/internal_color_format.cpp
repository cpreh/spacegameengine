//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/color_format.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/convert/internal_color_format.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::opengl::internal_color_format
sge::opengl::convert::internal_color_format(sge::opengl::color_format const _format)
{
  switch (_format)
  {
  case sge::opengl::color_format::a8:
    return sge::opengl::internal_color_format(GL_ALPHA8);
  case sge::opengl::color_format::l8:
    return sge::opengl::internal_color_format(GL_LUMINANCE8);
  case sge::opengl::color_format::r32f:
    return sge::opengl::internal_color_format(1);
  case sge::opengl::color_format::la8:
    return sge::opengl::internal_color_format(GL_LUMINANCE_ALPHA);
  case sge::opengl::color_format::rgb8:
    return sge::opengl::internal_color_format(GL_RGB8);
  case sge::opengl::color_format::bgr8:
  case sge::opengl::color_format::bgr32f:
    return sge::opengl::internal_color_format(3);
  case sge::opengl::color_format::rgba8:
    return sge::opengl::internal_color_format(GL_RGBA8);
  case sge::opengl::color_format::bgra8:
  case sge::opengl::color_format::rgba32f:
  case sge::opengl::color_format::bgra32f:
    return sge::opengl::internal_color_format(4);
  case sge::opengl::color_format::rgb32f:
    return sge::opengl::internal_color_format(GL_RGB32F);
  case sge::opengl::color_format::srgb8:
  case sge::opengl::color_format::sbgr8:
    return sge::opengl::internal_color_format(GL_SRGB8);
  case sge::opengl::color_format::srgba8:
  case sge::opengl::color_format::sbgra8:
    return sge::opengl::internal_color_format(GL_SRGB8_ALPHA8);
  }

  FCPPT_ASSERT_UNREACHABLE;
}
