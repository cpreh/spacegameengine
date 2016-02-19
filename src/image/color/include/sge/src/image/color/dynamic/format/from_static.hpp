/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_FROM_STATIC_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_FROM_STATIC_HPP_INCLUDED

#include <sge/image/color/a8_format.hpp>
#include <sge/image/color/bgr32f_format.hpp>
#include <sge/image/color/bgr8_format.hpp>
#include <sge/image/color/bgra32f_format.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/bgrx8_format.hpp>
#include <sge/image/color/l8_format.hpp>
#include <sge/image/color/la8_format.hpp>
#include <sge/image/color/r32f_format.hpp>
#include <sge/image/color/rgb32f_format.hpp>
#include <sge/image/color/rgb8_format.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/rgbx8_format.hpp>
#include <sge/image/color/sbgr8_format.hpp>
#include <sge/image/color/sbgra8_format.hpp>
#include <sge/image/color/srgb8_format.hpp>
#include <sge/image/color/srgba8_format.hpp>
#include <sge/image/color/detail/symbol.hpp>
#include <sge/src/image/color/dynamic/format/empty_c8_1.hpp>
#include <sge/src/image/color/dynamic/format/luminance_c8_1.hpp>
#include <sge/src/image/color/dynamic/format/luminance_c8_2.hpp>
#include <sge/src/image/color/dynamic/format/r_c32f_1.hpp>
#include <sge/src/image/color/dynamic/format/rgb_c32f_3.hpp>
#include <sge/src/image/color/dynamic/format/rgb_c32f_4.hpp>
#include <sge/src/image/color/dynamic/format/rgb_c8_3.hpp>
#include <sge/src/image/color/dynamic/format/rgb_c8_4.hpp>
#include <sge/src/image/color/dynamic/format/srgb_c8_3.hpp>
#include <sge/src/image/color/dynamic/format/srgb_c8_4.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{
namespace format
{

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::empty_c8_1 const &
from_static(
	sge::image::color::a8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::luminance_c8_1 const &
from_static(
	sge::image::color::l8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::r_c32f_1 const &
from_static(
	sge::image::color::r32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::luminance_c8_2 const &
from_static(
	sge::image::color::la8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c8_3 const &
from_static(
	sge::image::color::rgb8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c8_3 const &
from_static(
	sge::image::color::bgr8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c8_4 const &
from_static(
	sge::image::color::rgba8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c8_4 const &
from_static(
	sge::image::color::rgbx8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c8_4 const &
from_static(
	sge::image::color::bgra8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c8_4 const &
from_static(
	sge::image::color::bgrx8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c32f_3 const &
from_static(
	sge::image::color::rgb32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c32f_3 const &
from_static(
	sge::image::color::bgr32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c32f_4 const &
from_static(
	sge::image::color::rgba32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::rgb_c32f_4 const &
from_static(
	sge::image::color::bgra32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::srgb_c8_3 const &
from_static(
	sge::image::color::sbgr8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::srgb_c8_4 const &
from_static(
	sge::image::color::sbgra8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::srgb_c8_3 const &
from_static(
	sge::image::color::srgb8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::dynamic::format::srgb_c8_4 const &
from_static(
	sge::image::color::srgba8_format const &
);

}
}
}
}
}

#endif
