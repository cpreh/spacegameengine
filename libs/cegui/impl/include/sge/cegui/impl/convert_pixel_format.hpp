//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_CONVERT_PIXEL_FORMAT_HPP_INCLUDED
#define SGE_CEGUI_IMPL_CONVERT_PIXEL_FORMAT_HPP_INCLUDED

#include <sge/image/color/optional_format_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Texture.h>
#include <fcppt/config/external_end.hpp>


namespace sge::cegui::impl
{

sge::image::color::optional_format
convert_pixel_format(
	CEGUI::Texture::PixelFormat
);

}

#endif
