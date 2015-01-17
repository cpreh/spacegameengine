/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/src/image/color/dynamic/a8_format.hpp>
#include <sge/src/image/color/dynamic/bgr32f_format.hpp>
#include <sge/src/image/color/dynamic/bgr8_format.hpp>
#include <sge/src/image/color/dynamic/bgra32f_format.hpp>
#include <sge/src/image/color/dynamic/bgra8_format.hpp>
#include <sge/src/image/color/dynamic/bgrx8_format.hpp>
#include <sge/src/image/color/dynamic/c32f_1_format.hpp>
#include <sge/src/image/color/dynamic/c32f_3_format.hpp>
#include <sge/src/image/color/dynamic/c32f_4_format.hpp>
#include <sge/src/image/color/dynamic/c8_1_format.hpp>
#include <sge/src/image/color/dynamic/c8_2_format.hpp>
#include <sge/src/image/color/dynamic/c8_3_format.hpp>
#include <sge/src/image/color/dynamic/c8_4_format.hpp>
#include <sge/src/image/color/dynamic/from_static_format.hpp>
#include <sge/src/image/color/dynamic/l8_format.hpp>
#include <sge/src/image/color/dynamic/la8_format.hpp>
#include <sge/src/image/color/dynamic/r32f_format.hpp>
#include <sge/src/image/color/dynamic/rgb32f_format.hpp>
#include <sge/src/image/color/dynamic/rgb8_format.hpp>
#include <sge/src/image/color/dynamic/rgba32f_format.hpp>
#include <sge/src/image/color/dynamic/rgba8_format.hpp>
#include <sge/src/image/color/dynamic/rgbx8_format.hpp>
#include <sge/src/image/color/dynamic/sbgr8_format.hpp>
#include <sge/src/image/color/dynamic/sbgra8_format.hpp>
#include <sge/src/image/color/dynamic/srgb8_format.hpp>
#include <sge/src/image/color/dynamic/srgba8_format.hpp>


#define SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	dformat,\
	sformat\
)\
sge::image::color::dynamic::dformat const & \
sge::image::color::dynamic::from_static_format(\
	sge::image::color::sformat const &\
)\
{\
	return sge::image::color::dynamic::sformat;\
}

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_1_format,
	a8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_1_format,
	l8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c32f_1_format,
	r32f_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_2_format,
	la8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_3_format,
	rgb8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_3_format,
	bgr8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_4_format,
	rgba8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_4_format,
	rgbx8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_4_format,
	bgra8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_4_format,
	bgrx8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c32f_3_format,
	rgb32f_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c32f_3_format,
	bgr32f_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c32f_4_format,
	rgba32f_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c32f_4_format,
	bgra32f_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_3_format,
	srgb8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_4_format,
	srgba8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_3_format,
	sbgr8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(
	c8_4_format,
	sbgra8_format
)
