//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_FORMAT_FROM_STATIC_HPP_INCLUDED
#define SGE_IMAGE_COLOR_FORMAT_FROM_STATIC_HPP_INCLUDED

#include <sge/image/declare_format_from_static.hpp>
#include <sge/image/color/enable_if_has_format.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/tag.hpp> // IWYU pragma: keep
#include <sge/image/color/detail/pp_formats.hpp>
#include <sge/image/color/detail/symbol.hpp>
#include <sge/image/color/traits/format_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge::image::color
{

template <typename Format>
SGE_IMAGE_COLOR_DETAIL_SYMBOL
    sge::image::color::enable_if_has_format<Format, sge::image::color::format>
    format_from_static();

}

#define SGE_IMAGE_COLOR_DETAIL_DECLARE_FORMAT_FROM_STATIC(seq, _, format_arg) \
  extern template SGE_IMAGE_COLOR_DETAIL_SYMBOL sge::image::color::enable_if_has_format< \
      sge::image::color::BOOST_PP_CAT(format_arg, _format), \
      sge::image::color::format> \
  sge::image::color::format_from_static<sge::image::color::BOOST_PP_CAT(format_arg, _format)>(); \
  SGE_IMAGE_DECLARE_FORMAT_FROM_STATIC( \
      sge::image::color::tag, sge::image::color::BOOST_PP_CAT(format_arg, _format));

BOOST_PP_SEQ_FOR_EACH(
    SGE_IMAGE_COLOR_DETAIL_DECLARE_FORMAT_FROM_STATIC, _, SGE_IMAGE_COLOR_DETAIL_PP_FORMATS)

#endif
