//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/impl/convert_pixel_format.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Texture.h>
#include <fcppt/config/external_end.hpp>

sge::image::color::optional_format
sge::cegui::impl::convert_pixel_format(CEGUI::Texture::PixelFormat const _format)
{
  switch (_format)
  {
  case CEGUI::Texture::PF_RGB:
    return sge::image::color::optional_format(sge::image::color::format::rgb8);
  case CEGUI::Texture::PF_RGBA:
    return sge::image::color::optional_format(sge::image::color::format::rgba8);
  case CEGUI::Texture::PF_RGBA_4444:
  case CEGUI::Texture::PF_RGB_565:
  case CEGUI::Texture::PF_PVRTC2:
  case CEGUI::Texture::PF_PVRTC4:
  case CEGUI::Texture::PF_RGB_DXT1:
  case CEGUI::Texture::PF_RGBA_DXT1:
  case CEGUI::Texture::PF_RGBA_DXT3:
  case CEGUI::Texture::PF_RGBA_DXT5:
    return sge::image::color::optional_format();
  }

  FCPPT_ASSERT_UNREACHABLE;
}
