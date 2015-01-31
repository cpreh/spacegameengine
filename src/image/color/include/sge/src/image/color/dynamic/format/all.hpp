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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_ALL_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_ALL_HPP_INCLUDED

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
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


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

typedef
boost::mpl::vector10<
	sge::image::color::dynamic::format::empty_c8_1,
	sge::image::color::dynamic::format::luminance_c8_1,
	sge::image::color::dynamic::format::luminance_c8_2,
	sge::image::color::dynamic::format::rgb_c8_3,
	sge::image::color::dynamic::format::rgb_c8_4,
	sge::image::color::dynamic::format::r_c32f_1,
	sge::image::color::dynamic::format::rgb_c32f_3,
	sge::image::color::dynamic::format::rgb_c32f_4,
	sge::image::color::dynamic::format::srgb_c8_3,
	sge::image::color::dynamic::format::srgb_c8_4
>
all;

}
}
}
}
}

#endif
