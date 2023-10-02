//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/impl/traits/dynamic_copy_and_convert.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image/color/impl/traits/static_converter.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image/impl/algorithm/copy_and_convert_impl.hpp>
#include <sge/image/impl/algorithm/instantiate_copy_and_convert.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/algorithm/copy_and_convert.hpp>
#include <sge/image3d/traits/color_tag.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image3d/traits/dimension.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>

void sge::image3d::algorithm::copy_and_convert(
    sge::image3d::view::const_object const &_src,
    sge::image3d::view::object const &_dest,
    sge::image::algorithm::may_overlap const _overlap,
    sge::image::algorithm::uninitialized const _uninitialized)
{
  sge::image::algorithm::copy_and_convert<sge::image3d::tag>(_src, _dest, _overlap, _uninitialized);
}

SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY_AND_CONVERT(sge::image3d::tag);
