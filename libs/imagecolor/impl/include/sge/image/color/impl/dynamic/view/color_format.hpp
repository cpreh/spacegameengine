//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_COLOR_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_COLOR_FORMAT_HPP_INCLUDED

namespace sge::image::color::impl::dynamic::view
{

template <typename ImageFormat>
typename ImageFormat::color_format const &color_format(ImageFormat const &_format)
{
  return _format.format_store().get();
}

}

#endif
