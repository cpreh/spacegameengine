/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GUI_CANVAS_UTILITY_MAKE_FONT_CHANNEL_BLITTER_HPP_INCLUDED
#define SGE_GUI_CANVAS_UTILITY_MAKE_FONT_CHANNEL_BLITTER_HPP_INCLUDED

#include "font_channel_blitter.hpp"

namespace sge
{
namespace gui
{
namespace utility
{

template<
	typename FontColor,
	typename FontPixel,
	typename DstPixel
>
font_channel_blitter<
	FontColor,
	FontPixel,
	DstPixel
> const
make_font_channel_blitter(
	FontColor const &fontcolor,
	FontPixel const &font,
	DstPixel &result
)
{
	return
		font_channel_blitter<
			FontColor,
			FontPixel,
			DstPixel
		>(
			fontcolor,
			font,
			result
		);
}

}
}
}

#endif
