//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_FREETYPE_OPTIONAL_PIXEL_MODE_FWD_HPP_INCLUDED
#define SGE_PANGO_FREETYPE_OPTIONAL_PIXEL_MODE_FWD_HPP_INCLUDED

#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ft2build.h>
#include FT_IMAGE_H
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{
namespace freetype
{

typedef
fcppt::optional::object<
	FT_Pixel_Mode
>
optional_pixel_mode;

}
}
}

#endif
