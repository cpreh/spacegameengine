//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_ALL_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_ALL_HPP_INCLUDED

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
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{
namespace dynamic
{
namespace format
{

typedef
metal::list<
	sge::image::color::impl::dynamic::format::empty_c8_1,
	sge::image::color::impl::dynamic::format::luminance_c8_1,
	sge::image::color::impl::dynamic::format::luminance_c8_2,
	sge::image::color::impl::dynamic::format::rgb_c8_3,
	sge::image::color::impl::dynamic::format::rgb_c8_4,
	sge::image::color::impl::dynamic::format::r_c32f_1,
	sge::image::color::impl::dynamic::format::rgb_c32f_3,
	sge::image::color::impl::dynamic::format::rgb_c32f_4,
	sge::image::color::impl::dynamic::format::srgb_c8_3,
	sge::image::color::impl::dynamic::format::srgb_c8_4
>
all;

}
}
}
}
}
}

#endif
