//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/format.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/convert/color_format.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::image::color::format
sge::opengl::convert::color_format(sge::opengl::color_format const _format)
{
#define SGE_OPENGL_CONVERT_FORMAT(name) \
  case sge::opengl::color_format::name: \
    return sge::image::color::format::name

  switch (_format)
  {
    SGE_OPENGL_CONVERT_FORMAT(a8);
    SGE_OPENGL_CONVERT_FORMAT(l8);
    SGE_OPENGL_CONVERT_FORMAT(r32f);
    SGE_OPENGL_CONVERT_FORMAT(la8);
    SGE_OPENGL_CONVERT_FORMAT(rgb8);
    SGE_OPENGL_CONVERT_FORMAT(bgr8);
    SGE_OPENGL_CONVERT_FORMAT(rgba8);
    SGE_OPENGL_CONVERT_FORMAT(bgra8);
    SGE_OPENGL_CONVERT_FORMAT(rgb32f);
    SGE_OPENGL_CONVERT_FORMAT(bgr32f);
    SGE_OPENGL_CONVERT_FORMAT(rgba32f);
    SGE_OPENGL_CONVERT_FORMAT(bgra32f);
    SGE_OPENGL_CONVERT_FORMAT(srgb8);
    SGE_OPENGL_CONVERT_FORMAT(srgba8);
    SGE_OPENGL_CONVERT_FORMAT(sbgr8);
    SGE_OPENGL_CONVERT_FORMAT(sbgra8);
  }

  FCPPT_ASSERT_UNREACHABLE;
}
