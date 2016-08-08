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
#include <sge/image/color/srgb8_format.hpp>
#include <sge/image/color/srgba8_format.hpp>
#include <sge/image/color/impl/dynamic/format/a8.hpp>
#include <sge/image/color/impl/dynamic/format/bgr32f.hpp>
#include <sge/image/color/impl/dynamic/format/bgr8.hpp>
#include <sge/image/color/impl/dynamic/format/bgra32f.hpp>
#include <sge/image/color/impl/dynamic/format/bgra8.hpp>
#include <sge/image/color/impl/dynamic/format/bgrx8.hpp>
#include <sge/image/color/impl/dynamic/format/empty_c8_1.hpp>
#include <sge/image/color/impl/dynamic/format/from_static.hpp>
#include <sge/image/color/impl/dynamic/format/l8.hpp>
#include <sge/image/color/impl/dynamic/format/la8.hpp>
#include <sge/image/color/impl/dynamic/format/luminance_c8_1.hpp>
#include <sge/image/color/impl/dynamic/format/luminance_c8_2.hpp>
#include <sge/image/color/impl/dynamic/format/r32f.hpp>
#include <sge/image/color/impl/dynamic/format/r_c32f_1.hpp>
#include <sge/image/color/impl/dynamic/format/rgb32f.hpp>
#include <sge/image/color/impl/dynamic/format/rgb8.hpp>
#include <sge/image/color/impl/dynamic/format/rgb_c32f_3.hpp>
#include <sge/image/color/impl/dynamic/format/rgb_c32f_4.hpp>
#include <sge/image/color/impl/dynamic/format/rgb_c8_3.hpp>
#include <sge/image/color/impl/dynamic/format/rgb_c8_4.hpp>
#include <sge/image/color/impl/dynamic/format/rgba32f.hpp>
#include <sge/image/color/impl/dynamic/format/rgba8.hpp>
#include <sge/image/color/impl/dynamic/format/rgbx8.hpp>
#include <sge/image/color/impl/dynamic/format/sbgr8.hpp>
#include <sge/image/color/impl/dynamic/format/sbgra8.hpp>
#include <sge/image/color/impl/dynamic/format/srgb8.hpp>
#include <sge/image/color/impl/dynamic/format/srgb_c8_3.hpp>
#include <sge/image/color/impl/dynamic/format/srgb_c8_4.hpp>
#include <sge/image/color/impl/dynamic/format/srgba8.hpp>


#define SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	dformat,\
	sformat\
)\
sge::image::color::impl::dynamic::format::dformat const & \
sge::image::color::impl::dynamic::format::from_static(\
	sge::image::color::sformat ## _format const &\
)\
{\
	return \
		sge::image::color::impl::dynamic::format::sformat;\
}

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	empty_c8_1,
	a8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	luminance_c8_1,
	l8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	r_c32f_1,
	r32f
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	luminance_c8_2,
	la8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c8_3,
	rgb8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c8_3,
	bgr8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c8_4,
	rgba8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c8_4,
	rgbx8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c8_4,
	bgra8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c8_4,
	bgrx8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c32f_3,
	rgb32f
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c32f_3,
	bgr32f
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c32f_4,
	rgba32f
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	rgb_c32f_4,
	bgra32f
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	srgb_c8_3,
	srgb8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	srgb_c8_4,
	srgba8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	srgb_c8_3,
	sbgr8
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	srgb_c8_4,
	sbgra8
)
