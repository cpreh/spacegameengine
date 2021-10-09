//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/impl/view/checked_sub_impl.hpp>
#include <sge/image/impl/view/instantiate_checked_sub.hpp>
#include <sge/image2d/rect_fwd.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/view/checked_sub.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/image2d/view/sub_out_of_range.hpp>

sge::image2d::view::object sge::image2d::view::checked_sub(
    sge::image2d::view::object const &_view, sge::image2d::rect const &_rect)
{
  return sge::image::view::checked_sub<sge::image2d::tag>(_view, _rect);
}

sge::image2d::view::const_object sge::image2d::view::checked_sub(
    sge::image2d::view::const_object const &_view, sge::image2d::rect const &_rect)
{
  return sge::image::view::checked_sub<sge::image2d::tag>(_view, _rect);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CHECKED_SUB(sge::image2d::tag);
