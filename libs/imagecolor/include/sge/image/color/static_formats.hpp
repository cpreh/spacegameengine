//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_STATIC_FORMATS_HPP_INCLUDED
#define SGE_IMAGE_COLOR_STATIC_FORMATS_HPP_INCLUDED

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
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{

using
static_formats
=
metal::list<
	sge::image::color::a8_format,
	sge::image::color::l8_format,
	sge::image::color::r32f_format,
	sge::image::color::la8_format,
	sge::image::color::rgb8_format,
	sge::image::color::bgr8_format,
	sge::image::color::rgba8_format,
	sge::image::color::rgbx8_format,
	sge::image::color::bgra8_format,
	sge::image::color::bgrx8_format,
	sge::image::color::rgb32f_format,
	sge::image::color::bgr32f_format,
	sge::image::color::rgba32f_format,
	sge::image::color::bgra32f_format,
	sge::image::color::srgb8_format,
	sge::image::color::srgba8_format,
	sge::image::color::sbgr8_format,
	sge::image::color::sbgra8_format
>;

}
}
}

#endif
