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


#ifndef SGE_RENDERER_COLOR_FORMAT_STATIC_HPP_INCLUDED
#define SGE_RENDERER_COLOR_FORMAT_STATIC_HPP_INCLUDED

#include "color.hpp"
#include "color_format.hpp"
#include <boost/mpl/integral_c.hpp>

namespace sge
{
namespace renderer
{

template<typename Color>
struct color_format_static;

template<>
struct color_format_static<rgba8_color>
: boost::mpl::integral_c<
	color_format::type,
	color_format::rgba8
>{};

template<>
struct color_format_static<bgra8_color>
: boost::mpl::integral_c<
	color_format::type,
	color_format::bgra8
>{};

template<>
struct color_format_static<argb8_color>
: boost::mpl::integral_c<
	color_format::type,
	color_format::argb8
>{};

template<>
struct color_format_static<rgba_f32_color>
: boost::mpl::integral_c<
	color_format::type,
	color_format::rgbaf32
>{};

}
}

#endif
