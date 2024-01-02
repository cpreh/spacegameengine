//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_FORMAT_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/impl/view/format_impl.hpp> // IWYU pragma: keep
#include <sge/image/impl/view/instantiate_const_nonconst.hpp> // IWYU pragma: keep
#include <sge/image/traits/image/color_tag.hpp> // IWYU pragma: keep
#include <sge/image/traits/pixel/format_fwd.hpp> // IWYU pragma: keep

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_FORMAT_BASE(tag, object_type) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
      sge::image::traits::pixel::format<sge::image::traits::image::color_tag<tag>> \
      sge::image::view::format<tag>(sge::image::view::object_type<tag> const &)

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_FORMAT(tag) \
  SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CONST_NONCONST(tag, SGE_IMAGE_IMPL_VIEW_INSTANTIATE_FORMAT_BASE)

#endif
