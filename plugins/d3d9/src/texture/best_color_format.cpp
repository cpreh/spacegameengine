//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/texture/best_color_format.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::image::color::format
sge::d3d9::texture::best_color_format(sge::image::color::format const _format)
{
  // TODO: Convert d3d9 formats directly, because this is confusing.
  // Also fix the srgb types.
  switch (_format)
  {
  case sge::image::color::format::a8:
  case sge::image::color::format::l8:
  case sge::image::color::format::r32f:
  case sge::image::color::format::la8:
  case sge::image::color::format::bgra8:
  case sge::image::color::format::rgbx8:
  case sge::image::color::format::bgrx8:
  case sge::image::color::format::rgba32f:
  case sge::image::color::format::bgr8:
    return _format;
  case sge::image::color::format::rgb8:
    return sge::image::color::format::bgr8;
  case sge::image::color::format::rgba8:
  case sge::image::color::format::srgba8:
  case sge::image::color::format::srgb8:
    return sge::image::color::format::bgra8;
  case sge::image::color::format::rgb32f:
  case sge::image::color::format::bgr32f:
  case sge::image::color::format::bgra32f:
    return sge::image::color::format::rgba32f;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
