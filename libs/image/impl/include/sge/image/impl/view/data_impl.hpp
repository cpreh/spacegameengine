//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_DATA_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_DATA_IMPL_HPP_INCLUDED

#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/impl/view/data_any.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/data.hpp>
#include <sge/image/view/object_fwd.hpp>

template <typename Tag>
sge::image::raw_pointer sge::image::view::data(sge::image::view::object<Tag> const &_view)
{
  return sge::image::impl::view::data_any<sge::image::raw_pointer>(_view);
}

template <typename Tag>
sge::image::const_raw_pointer
sge::image::view::data(sge::image::view::const_object<Tag> const &_view)
{
  return sge::image::impl::view::data_any<sge::image::const_raw_pointer>(_view);
}

#endif
