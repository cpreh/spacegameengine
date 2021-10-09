//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/impl/algorithm/fill_impl.hpp>
#include <sge/image/impl/algorithm/instantiate_fill.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/object.hpp>

void sge::image2d::algorithm::fill(
    sge::image2d::view::object const &_dest,
    sge::image::color::any::object const &_col,
    sge::image::algorithm::uninitialized const _uninitialized)
{
  sge::image::algorithm::fill<sge::image2d::tag>(_dest, _col, _uninitialized);
}

SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_FILL(sge::image2d::tag);
