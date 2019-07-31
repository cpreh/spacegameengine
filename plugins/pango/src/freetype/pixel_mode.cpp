//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/pango/freetype/pixel_mode.hpp>
#include <sge/pango/freetype/optional_pixel_mode.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ft2build.h>
#include FT_IMAGE_H
#include <fcppt/config/external_end.hpp>


sge::pango::freetype::optional_pixel_mode
sge::pango::freetype::pixel_mode(
	sge::image::color::format const _format
)
{
	switch(
		_format
	)
	{
	case sge::image::color::format::a8:
	case sge::image::color::format::l8:
		return
			sge::pango::freetype::optional_pixel_mode{
				FT_PIXEL_MODE_GRAY
			};
	case sge::image::color::format::bgra8:
		return
			sge::pango::freetype::optional_pixel_mode{
    				FT_PIXEL_MODE_BGRA
			};
	case sge::image::color::format::r32f:
	case sge::image::color::format::la8:
	case sge::image::color::format::rgb8:
	case sge::image::color::format::bgr8:
	case sge::image::color::format::rgba8:
	case sge::image::color::format::rgbx8:
	case sge::image::color::format::bgrx8:
	case sge::image::color::format::rgb32f:
	case sge::image::color::format::bgr32f:
	case sge::image::color::format::rgba32f:
	case sge::image::color::format::bgra32f:
	case sge::image::color::format::srgb8:
	case sge::image::color::format::srgba8:
	case sge::image::color::format::sbgr8:
	case sge::image::color::format::sbgra8:
		return
			sge::pango::freetype::optional_pixel_mode{};
	}

	FCPPT_ASSERT_UNREACHABLE;
}
