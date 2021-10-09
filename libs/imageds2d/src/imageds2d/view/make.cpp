//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/raw_pointer.hpp>
#include <sge/image/ds/format.hpp>
#include <sge/image/ds/impl/traits/format_map.hpp>
#include <sge/image/ds/traits/format_fwd.hpp>
#include <sge/image/impl/view/instantiate_make.hpp>
#include <sge/image/impl/view/make_impl.hpp>
#include <sge/imageds2d/dim.hpp>
#include <sge/imageds2d/pitch.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/traits/color_tag.hpp>
#include <sge/imageds2d/traits/dimension.hpp>
#include <sge/imageds2d/view/make.hpp>
#include <sge/imageds2d/view/object.hpp>

sge::imageds2d::view::object sge::imageds2d::view::make(
    sge::image::raw_pointer const _data,
    sge::imageds2d::dim const &_dim,
    sge::image::ds::format const _format,
    sge::imageds2d::pitch const &_pitch)
{
  return sge::image::view::make<sge::imageds2d::tag>(_data, _dim, _format, _pitch);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE(sge::imageds2d::tag);
