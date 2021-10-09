//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PANGO_FREETYPE_PIXEL_MODE_HPP_INCLUDED
#define SGE_PANGO_FREETYPE_PIXEL_MODE_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/pango/freetype/optional_pixel_mode.hpp>

namespace sge::pango::freetype
{

sge::pango::freetype::optional_pixel_mode pixel_mode(sge::image::color::format);

}

#endif
