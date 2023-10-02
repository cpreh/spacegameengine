//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/format.hpp>
#include <sge/image/color/impl/traits/format_map.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image/color/traits/format_fwd.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image/impl/view/format_impl.hpp>
#include <sge/image/impl/view/instantiate_format.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/format.hpp>
#include <sge/image3d/view/object.hpp>

sge::image::color::format sge::image3d::view::format(sge::image3d::view::object const &_view)
{
  return sge::image::view::format<sge::image3d::tag>(_view);
}

sge::image::color::format sge::image3d::view::format(sge::image3d::view::const_object const &_view)
{
  return sge::image::view::format<sge::image3d::tag>(_view);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_FORMAT(sge::image3d::tag);
