//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_FORMAT_CHANNEL_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_FORMAT_CHANNEL_HPP_INCLUDED

#include <sge/image/size_type.hpp>

namespace sge
{
namespace image
{
namespace color
{
namespace impl
{
namespace dynamic
{
namespace view
{

template <typename ImageFormat>
typename ImageFormat::color_format::available_channels
format_channel(ImageFormat const &_format, sge::image::size_type const _index)
{
  return _format.format_store().get()->order[_index];
}

}
}
}
}
}
}

#endif
