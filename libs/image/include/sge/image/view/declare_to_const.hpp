//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_VIEW_DECLARE_TO_CONST_HPP_INCLUDED
#define SGE_IMAGE_VIEW_DECLARE_TO_CONST_HPP_INCLUDED

#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/view/const_object_fwd.hpp> // IWYU pragma: keep
#include <sge/image/view/object_fwd.hpp> // IWYU pragma: keep
#include <sge/image/view/to_const.hpp> // IWYU pragma: keep

#define SGE_IMAGE_VIEW_DECLARE_TO_CONST(tag) \
  extern template SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL sge::image::view::const_object<tag> \
  sge::image::view::to_const(sge::image::view::object<tag> const &)

#endif
