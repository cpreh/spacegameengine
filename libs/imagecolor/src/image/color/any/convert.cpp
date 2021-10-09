//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/color/a8_format.hpp>
#include <sge/image/color/bgr32f_format.hpp>
#include <sge/image/color/bgr8_format.hpp>
#include <sge/image/color/bgra32f_format.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/bgrx8_format.hpp>
#include <sge/image/color/enable_if_has_format.hpp>
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
#include <sge/image/color/tag.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/detail/pp_formats.hpp>
#include <sge/image/color/impl/traits/static_converter.hpp>
#include <sge/image/color/traits/static_formats.hpp>
#include <sge/image/impl/pixel/convert_impl.hpp>
#include <sge/image/impl/pixel/instantiate_convert.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>

template <typename Format>
sge::image::color::enable_if_has_format<Format, sge::image::pixel::mizuiro_type<Format>>
sge::image::color::any::convert(sge::image::color::any::object const &_color)
{
  return sge::image::pixel::convert<sge::image::color::tag, Format>(_color);
}

#define SGE_IMAGE_COLOR_INSTANTIATE_CONVERT(seq, _, format_arg) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION sge::image::color::enable_if_has_format< \
      sge::image::color::BOOST_PP_CAT(format_arg, _format), \
      sge::image::pixel::mizuiro_type<sge::image::color::BOOST_PP_CAT(format_arg, _format)>> \
  sge::image::color::any::convert<sge::image::color::BOOST_PP_CAT(format_arg, _format)>( \
      sge::image::color::any::object const &); \
  SGE_IMAGE_IMPL_PIXEL_INSTANTIATE_CONVERT( \
      sge::image::color::tag, sge::image::color::BOOST_PP_CAT(format_arg, _format));

BOOST_PP_SEQ_FOR_EACH(SGE_IMAGE_COLOR_INSTANTIATE_CONVERT, _, SGE_IMAGE_COLOR_DETAIL_PP_FORMATS)
