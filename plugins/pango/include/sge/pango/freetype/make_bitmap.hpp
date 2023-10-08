//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PANGO_FREETYPE_MAKE_BITMAP_HPP_INCLUDED
#define SGE_PANGO_FREETYPE_MAKE_BITMAP_HPP_INCLUDED

#include <sge/font/view_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ft2build.h> // NOLINT(misc-include-cleaner)
#include <freetype/freetype.h> // NOLINT(misc-include-cleaner)
#include <freetype/ftimage.h>
#include <fcppt/config/external_end.hpp>

namespace sge::pango::freetype
{

FT_Bitmap make_bitmap(sge::font::view const &);

}

#endif
