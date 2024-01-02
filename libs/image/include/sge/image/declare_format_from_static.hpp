//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_DECLARE_FORMAT_FROM_STATIC_HPP_INCLUDED
#define SGE_IMAGE_DECLARE_FORMAT_FROM_STATIC_HPP_INCLUDED

#include <sge/image/enable_if_has_format.hpp> // IWYU pragma: keep
#include <sge/image/format_from_static.hpp> // IWYU pragma: keep
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp> // IWYU pragma: keep

#define SGE_IMAGE_DECLARE_FORMAT_FROM_STATIC(tag, format_arg) \
  extern template SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL \
      sge::image::enable_if_has_format<tag, format_arg, sge::image::traits::pixel::format<tag>> \
      sge::image::format_from_static<tag, format_arg>()

#endif
