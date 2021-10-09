//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/ds/traits/format_fwd.hpp>
#include <sge/image/impl/algorithm/copy_impl.hpp>
#include <sge/image/impl/algorithm/instantiate_copy.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/algorithm/copy.hpp>
#include <sge/imageds2d/algorithm/invalid_copy.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/format.hpp>
#include <sge/imageds2d/view/object.hpp>

void sge::imageds2d::algorithm::copy(
    sge::imageds2d::view::const_object const &_src,
    sge::imageds2d::view::object const &_dest,
    sge::image::algorithm::may_overlap const _overlap,
    sge::image::algorithm::uninitialized const _uninitialized)
{
  sge::image::algorithm::copy<sge::imageds2d::tag>(_src, _dest, _overlap, _uninitialized);
}

SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY(sge::imageds2d::tag);
