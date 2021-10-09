//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_FORMAT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_FORMAT_IMPL_HPP_INCLUDED

#include <sge/image/impl/view/format_any.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/view/format.hpp>

template <typename Tag>
sge::image::traits::pixel::format<sge::image::traits::image::color_tag<Tag>>
sge::image::view::format(sge::image::view::object<Tag> const &_view)
{
  return sge::image::impl::view::format_any<sge::image::traits::image::color_tag<Tag>>(_view);
}

template <typename Tag>
sge::image::traits::pixel::format<sge::image::traits::image::color_tag<Tag>>
sge::image::view::format(sge::image::view::const_object<Tag> const &_view)
{
  return sge::image::impl::view::format_any<sge::image::traits::image::color_tag<Tag>>(_view);
}

#endif
