//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/color_format.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/assert/unreachable.hpp>

D3DFORMAT
sge::d3d9::convert::color_format(sge::image::color::format const _format)
{
  switch (_format)
  {
  case sge::image::color::format::a8:
    return D3DFMT_A8;
  case sge::image::color::format::l8:
    return D3DFMT_L8;
  case sge::image::color::format::r32f:
    return D3DFMT_R32F;
  case sge::image::color::format::la8:
    return D3DFMT_A8L8;
  case sge::image::color::format::bgr8:
  case sge::image::color::format::sbgr8:
    return D3DFMT_R8G8B8;
  case sge::image::color::format::rgba8:
  case sge::image::color::format::srgba8:
    return D3DFMT_A8B8G8R8;
  case sge::image::color::format::bgra8:
  case sge::image::color::format::sbgra8:
    return D3DFMT_A8R8G8B8;
  case sge::image::color::format::rgbx8:
    return D3DFMT_X8B8G8R8;
  case sge::image::color::format::bgrx8:
    return D3DFMT_X8R8G8B8;
  case sge::image::color::format::rgba32f:
    return D3DFMT_A32B32G32R32F;
  // FIXME: Use optional_format
  case sge::image::color::format::rgb8:
  case sge::image::color::format::srgb8:
  case sge::image::color::format::rgb32f:
  case sge::image::color::format::bgr32f:
  case sge::image::color::format::bgra32f:
    break;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
