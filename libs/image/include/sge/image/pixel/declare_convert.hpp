//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_PIXEL_DECLARE_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_PIXEL_DECLARE_CONVERT_HPP_INCLUDED

#include <sge/image/enable_if_has_format.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/pixel/convert.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/image/pixel/object_fwd.hpp>

#define SGE_IMAGE_PIXEL_DECLARE_CONVERT(tag, format) \
  extern template SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL \
      sge::image::enable_if_has_format<tag, format, sge::image::pixel::mizuiro_type<format>> \
      sge::image::pixel::convert<tag, format>(sge::image::pixel::object<tag> const &)

#endif
