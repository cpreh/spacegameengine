//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_FROM_STATIC_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_FROM_STATIC_HPP_INCLUDED

#include <sge/image/color/impl/dynamic/format/from_static.hpp>
#include <sge/image/color/impl/dynamic/format/from_static_type.hpp>
#include <sge/image/view/basic_format.hpp>
#include <sge/image/view/mizuiro_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

namespace sge::image::color::impl::dynamic::view
{

template <typename View>
sge::image::view::mizuiro_type<
    sge::image::view::basic_format<
        View::dim::static_size,
        sge::image::color::impl::dynamic::format::from_static_type<
            typename View::format::color_format>>,
    typename View::constness>
from_static(View const &_view)
{
  using dest_type = sge::image::view::mizuiro_type<
      sge::image::view::basic_format<
          View::dim::static_size,
          sge::image::color::impl::dynamic::format::from_static_type<
              typename View::format::color_format>>,
      typename View::constness>;

  using dest_format = typename dest_type::format;

  return dest_type(
      _view.size(),
      _view.data(),
      _view.pitch(),
      typename dest_type::format_store_type(dest_format(typename dest_format::format_store_type(
          std::cref(sge::image::color::impl::dynamic::format::from_static(
              typename View::format::color_format()))))));
}

}

#endif
