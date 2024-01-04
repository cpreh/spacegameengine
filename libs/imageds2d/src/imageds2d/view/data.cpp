//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/impl/view/data_impl.hpp>
#include <sge/image/impl/view/instantiate_data.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/data.hpp>
#include <sge/imageds2d/view/object.hpp>

sge::image::raw_pointer sge::imageds2d::view::data(sge::imageds2d::view::object const &_view)
{
  return sge::image::view::data<sge::imageds2d::tag>(_view);
}

sge::image::const_raw_pointer
sge::imageds2d::view::data(sge::imageds2d::view::const_object const &_view)
{
  return sge::image::view::data<sge::imageds2d::tag>(_view);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_DATA(sge::imageds2d::tag);
