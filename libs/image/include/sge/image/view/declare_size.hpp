//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_VIEW_DECLARE_SIZE_HPP_INCLUDED
#define SGE_IMAGE_VIEW_DECLARE_SIZE_HPP_INCLUDED

#include <sge/image/dim_fwd.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <sge/image/view/size.hpp>

#define SGE_IMAGE_VIEW_DECLARE_SIZE(tag) \
  extern template SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL sge::image::dim<tag> sge::image::view::size( \
      sge::image::view::object<tag> const &); \
\
  extern template SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL sge::image::dim<tag> sge::image::view::size( \
      sge::image::view::const_object<tag> const &)

#endif
