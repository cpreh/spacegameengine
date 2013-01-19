/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_COLOR_RGBA8_FROM_HEX_STRING_HPP_INCLUDED
#define SGE_IMAGE_COLOR_RGBA8_FROM_HEX_STRING_HPP_INCLUDED

#include <sge/image/color/rgb8_from_hex_string.hpp>
#include <sge/image/color/rgba8.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>


namespace sge
{
namespace image
{
namespace color
{
template<typename String>
sge::image::color::rgba8 const
rgba8_from_hex_string(
	String const &_string,
	sge::image::color::rgba8::format::channel_type const alpha)
{
	sge::image::color::rgb8 const rgb(
		sge::image::color::rgb8_from_hex_string(
			_string));

	return
		sge::image::color::rgba8(
			(sge::image::color::init::red() = rgb.get(mizuiro::color::channel::red()))
			(sge::image::color::init::green() = rgb.get(mizuiro::color::channel::green()))
			(sge::image::color::init::blue() = rgb.get(mizuiro::color::channel::blue()))
			(sge::image::color::init::alpha() = alpha));
}
}
}
}

#endif
