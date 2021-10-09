//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/impl/view/instantiate_to_const.hpp>
#include <sge/image/impl/view/to_const_impl.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/object.hpp>
#include <sge/imageds2d/view/to_const.hpp>

sge::imageds2d::view::const_object
sge::imageds2d::view::to_const(sge::imageds2d::view::object const &_view)
{
  return sge::image::view::to_const<sge::imageds2d::tag>(_view);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_TO_CONST(sge::imageds2d::tag);
