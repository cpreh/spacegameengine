//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/impl/traits/format_map.hpp>
#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/impl/view/instantiate_make_const.hpp>
#include <sge/image/impl/view/make_const_impl.hpp>
#include <sge/image3d/dim_fwd.hpp>
#include <sge/image3d/pitch_fwd.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/traits/color_tag.hpp>
#include <sge/image3d/traits/dimension.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/make_const.hpp>

sge::image3d::view::const_object sge::image3d::view::make_const(
    sge::image::const_raw_pointer const _data,
    sge::image3d::dim const &_dim,
    sge::image::color::format const _format,
    sge::image3d::pitch const &_pitch)
{
  return sge::image::view::make_const<sge::image3d::tag>(_data, _dim, _format, _pitch);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE_CONST(sge::image3d::tag);
