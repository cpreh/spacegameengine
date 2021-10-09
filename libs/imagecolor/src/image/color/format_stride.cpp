//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/size_type.hpp>
#include <sge/image/color/element_count.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_element_size.hpp>
#include <sge/image/color/format_stride.hpp>

sge::image::size_type sge::image::color::format_stride(sge::image::color::format const _format)
{
  return sge::image::color::element_count(_format) *
         sge::image::color::format_element_size(_format);
}
