//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/impl/view/checked_sub_impl.hpp>
#include <sge/image/impl/view/instantiate_checked_sub.hpp>
#include <sge/image3d/box_fwd.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/view/checked_sub.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/image3d/view/size.hpp>
#include <sge/image3d/view/sub.hpp>
#include <sge/image3d/view/sub_out_of_range.hpp>

sge::image3d::view::object sge::image3d::view::checked_sub(
    sge::image3d::view::object const &_view, sge::image3d::box const &_box)
{
  return sge::image::view::checked_sub<sge::image3d::tag>(_view, _box);
}

sge::image3d::view::const_object sge::image3d::view::checked_sub(
    sge::image3d::view::const_object const &_view, sge::image3d::box const &_box)
{
  return sge::image::view::checked_sub<sge::image3d::tag>(_view, _box);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CHECKED_SUB(sge::image3d::tag);
