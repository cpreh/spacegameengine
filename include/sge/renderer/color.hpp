/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_COLOR_HPP_INCLUDED
#define SGE_RENDERER_COLOR_HPP_INCLUDED

#include "../typeswitch.hpp"
#include "../export.hpp"

#include <boost/gil/pixel.hpp>
#include <boost/gil/rgba.hpp>
#include <boost/gil/gray.hpp>

namespace sge
{
namespace renderer
{

typedef uint8 pixel_channel_8;
typedef float pixel_channel_f32;

typedef boost::gil::pixel<
	pixel_channel_8,
	boost::gil::rgba_layout_t
> rgba8_pixel;

typedef rgba8_pixel const rgba8c_pixel;

typedef boost::gil::pixel<
	pixel_channel_8,
	boost::gil::argb_layout_t
> argb8_pixel;

typedef argb8_pixel const argb8c_pixel;

typedef boost::gil::pixel<
	pixel_channel_f32,
	boost::gil::rgba_layout_t
> rgba_f32_pixel;

typedef boost::gil::pixel<
	uint8,
	boost::gil::gray_layout_t
> gray8_pixel;

#ifdef SGE_USE_ARGB
typedef argb8_pixel color;
typedef argb_f32_pixel colorf;
#else
typedef rgba8_pixel color;
typedef rgba_f32_pixel colorf;
#endif

SGE_SYMBOL color const make_color_rgba(
	pixel_channel_8 r,
	pixel_channel_8 g,
	pixel_channel_8 b,
	pixel_channel_8 a);

}
}

#endif
