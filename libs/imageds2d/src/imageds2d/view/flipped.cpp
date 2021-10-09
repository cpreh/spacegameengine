//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/impl/view/flipped_impl.hpp>
#include <sge/image/impl/view/instantiate_flipped.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/flipped.hpp>
#include <sge/imageds2d/view/object.hpp>

sge::imageds2d::view::object
sge::imageds2d::view::flipped(sge::imageds2d::view::object const &_view)
{
  return sge::image::view::flipped<sge::imageds2d::tag>(_view);
}

sge::imageds2d::view::const_object
sge::imageds2d::view::flipped(sge::imageds2d::view::const_object const &_view)
{
  return sge::image::view::flipped<sge::imageds2d::tag>(_view);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_FLIPPED(sge::imageds2d::tag);
