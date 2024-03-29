//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PANGO_FREETYPE_OPTIONAL_PIXEL_MODE_FWD_HPP_INCLUDED
#define SGE_PANGO_FREETYPE_OPTIONAL_PIXEL_MODE_FWD_HPP_INCLUDED

#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ft2build.h> // IWYU pragma: keep
#include <freetype/freetype.h> // IWYU pragma: keep
#include <freetype/ftimage.h>
#include <fcppt/config/external_end.hpp>

namespace sge::pango::freetype
{

using optional_pixel_mode = fcppt::optional::object<FT_Pixel_Mode>;

}

#endif
