//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/impl/algorithm/compare_impl.hpp>
#include <sge/image/impl/algorithm/instantiate_compare.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/algorithm/compare.hpp>
#include <sge/image3d/view/const_object.hpp>

bool sge::image3d::algorithm::compare(
    sge::image3d::view::const_object const &_src1, sge::image3d::view::const_object const &_src2)
{
  return sge::image::algorithm::compare<sge::image3d::tag>(_src1, _src2);
}

SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COMPARE(sge::image3d::tag);
