//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/impl/view/flipped_impl.hpp>
#include <sge/image/impl/view/instantiate_flipped.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/flipped.hpp>
#include <sge/image2d/view/object.hpp>

sge::image2d::view::object sge::image2d::view::flipped(sge::image2d::view::object const &_view)
{
  return sge::image::view::flipped<sge::image2d::tag>(_view);
}

sge::image2d::view::const_object
sge::image2d::view::flipped(sge::image2d::view::const_object const &_view)
{
  return sge::image::view::flipped<sge::image2d::tag>(_view);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_FLIPPED(sge::image2d::tag);
