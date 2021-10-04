//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_FROM_STATIC_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_FROM_STATIC_HPP_INCLUDED

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
#include <sge/image/color/impl/dynamic/format/empty_c8_1.hpp>
#include <sge/image/color/impl/dynamic/format/luminance_c8_1.hpp>
#include <sge/image/color/impl/dynamic/format/luminance_c8_2.hpp>
#include <sge/image/color/impl/dynamic/format/r_c32f_1.hpp>
#include <sge/image/color/impl/dynamic/format/rgb_c32f_3.hpp>
#include <sge/image/color/impl/dynamic/format/rgb_c32f_4.hpp>
#include <sge/image/color/impl/dynamic/format/rgb_c8_3.hpp>
#include <sge/image/color/impl/dynamic/format/rgb_c8_4.hpp>
#include <sge/image/color/impl/dynamic/format/srgb_c8_3.hpp>
#include <sge/image/color/impl/dynamic/format/srgb_c8_4.hpp>


namespace sge::image::color::impl::dynamic::format
{

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::empty_c8_1 const &
from_static(
	sge::image::color::a8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::luminance_c8_1 const &
from_static(
	sge::image::color::l8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::r_c32f_1 const &
from_static(
	sge::image::color::r32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::luminance_c8_2 const &
from_static(
	sge::image::color::la8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c8_3 const &
from_static(
	sge::image::color::rgb8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c8_3 const &
from_static(
	sge::image::color::bgr8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c8_4 const &
from_static(
	sge::image::color::rgba8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c8_4 const &
from_static(
	sge::image::color::rgbx8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c8_4 const &
from_static(
	sge::image::color::bgra8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c8_4 const &
from_static(
	sge::image::color::bgrx8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c32f_3 const &
from_static(
	sge::image::color::rgb32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c32f_3 const &
from_static(
	sge::image::color::bgr32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c32f_4 const &
from_static(
	sge::image::color::rgba32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::rgb_c32f_4 const &
from_static(
	sge::image::color::bgra32f_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::srgb_c8_3 const &
from_static(
	sge::image::color::sbgr8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::srgb_c8_4 const &
from_static(
	sge::image::color::sbgra8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::srgb_c8_3 const &
from_static(
	sge::image::color::srgb8_format const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::impl::dynamic::format::srgb_c8_4 const &
from_static(
	sge::image::color::srgba8_format const &
);

}

#endif
