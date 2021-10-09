//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_CHECKED_SUB_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_CHECKED_SUB_IMPL_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/image/impl/view/checked_sub_any.hpp>
#include <sge/image/view/checked_sub.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>

template <typename Tag>
sge::image::view::object<Tag> sge::image::view::checked_sub(
    sge::image::view::object<Tag> const &_view, sge::image::box<Tag> const &_box)
{
  return sge::image::impl::view::checked_sub_any<Tag>(_view, _box);
}

template <typename Tag>
sge::image::view::const_object<Tag> sge::image::view::checked_sub(
    sge::image::view::const_object<Tag> const &_view, sge::image::box<Tag> const &_box)
{
  return sge::image::impl::view::checked_sub_any<Tag>(_view, _box);
}

#endif
