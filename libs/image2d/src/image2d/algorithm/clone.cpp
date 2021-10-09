//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/impl/algorithm/clone_impl.hpp>
#include <sge/image/impl/algorithm/instantiate_clone.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/algorithm/clone.hpp>
#include <sge/image2d/store/object.hpp>
#include <sge/image2d/view/const_object.hpp>

sge::image2d::store::object
sge::image2d::algorithm::clone(sge::image2d::view::const_object const &_view)
{
  return sge::image::algorithm::clone<sge::image2d::tag>(_view);
}

SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_CLONE(sge::image2d::tag);
