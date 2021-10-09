//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_FLIPPED_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_FLIPPED_IMPL_HPP_INCLUDED

#include <sge/image/impl/view/flipped_any.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/flipped.hpp>
#include <sge/image/view/object.hpp>

template <typename Tag>
sge::image::view::object<Tag> sge::image::view::flipped(sge::image::view::object<Tag> const &_view)
{
  return sge::image::impl::view::flipped_any(_view);
}

template <typename Tag>
sge::image::view::const_object<Tag>
sge::image::view::flipped(sge::image::view::const_object<Tag> const &_view)
{
  return sge::image::impl::view::flipped_any(_view);
}

#endif
