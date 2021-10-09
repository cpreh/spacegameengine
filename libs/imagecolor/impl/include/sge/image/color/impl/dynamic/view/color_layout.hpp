//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_COLOR_LAYOUT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_COLOR_LAYOUT_HPP_INCLUDED

#include <sge/image/color/impl/dynamic/view/color_format.hpp>
#include <sge/image/color/impl/dynamic/view/image_format.hpp>

namespace sge::image::color::impl::dynamic::view
{

template <typename View>
typename View::format::color_format::channel_array const &color_layout(View const &_view)
{
  return sge::image::color::impl::dynamic::view::color_format(
             sge::image::color::impl::dynamic::view::image_format(_view))
      .channels;
}

}

#endif
