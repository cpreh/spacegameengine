//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_CHECKED_SUB_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_CHECKED_SUB_ANY_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/image/impl/view/checked_sub_condition.hpp>
#include <sge/image/view/sub.hpp>

namespace sge::image::impl::view
{

template <typename Tag, typename View>
View checked_sub_any(View const &_view, sge::image::box<Tag> const &_box)
{
  sge::image::impl::view::checked_sub_condition<Tag>(_view, _box);

  return sge::image::view::sub<Tag>(_view, _box);
}

}

#endif
