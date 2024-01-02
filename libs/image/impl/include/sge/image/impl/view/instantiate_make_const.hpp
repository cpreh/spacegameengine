//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE_CONST_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE_CONST_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/const_raw_pointer.hpp> // IWYU pragma: keep
#include <sge/image/dim_fwd.hpp> // IWYU pragma: keep
#include <sge/image/pitch_fwd.hpp> // IWYU pragma: keep
#include <sge/image/impl/view/make_const_impl.hpp> // IWYU pragma: keep
#include <sge/image/traits/image/color_tag.hpp> // IWYU pragma: keep
#include <sge/image/traits/pixel/format_fwd.hpp> // IWYU pragma: keep
#include <sge/image/view/const_object.hpp> // IWYU pragma: keep

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE_CONST(Tag) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION sge::image::view::const_object<Tag> \
  sge::image::view::make_const<Tag>( \
      sge::image::const_raw_pointer const, \
      sge::image::dim<Tag> const &, \
      sge::image::traits::pixel::format<sge::image::traits::image::color_tag<Tag>>, \
      sge::image::pitch<Tag> const &)

#endif
