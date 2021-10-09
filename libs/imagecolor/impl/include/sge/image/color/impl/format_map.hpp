//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_FORMAT_MAP_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_FORMAT_MAP_HPP_INCLUDED

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
#include <sge/image/color/detail/pp_formats.hpp>
#include <sge/image/color/impl/make_format_pair.hpp>
#include <sge/image/impl/format_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge::image::color::impl
{

using format_map = sge::image::impl::format_map<BOOST_PP_SEQ_FOR_EACH_I(
    SGE_IMAGE_COLOR_IMPL_MAKE_FORMAT_PAIR, _, SGE_IMAGE_COLOR_DETAIL_PP_FORMATS)>;

}

#endif
