/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/exception.hpp>
#include <sge/image/color/format.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/to_sge_format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/diff.hpp>


sge::image::color::format::type
sge::libpng::to_sge_format(
	png_byte const _color_type,
	png_byte const _bit_depth,
	sge::libpng::gamma_value const &_gamma_value
)
{
	// For now, we assume that all png images have a gamma of 2.2 (or
	// 0.45455 as a reciprocal), which indicates sRGB. If we have
	// sRGB, we return the corresponding format. The gamma value,
	// however, could be off, in which case we have to look further
	// into it and maybe return a different color format.
	FCPPT_ASSERT_PRE(
		fcppt::math::diff(
			_gamma_value.get(),
			static_cast<sge::libpng::gamma_value::value_type>(
				0.45455)) <
		static_cast<sge::libpng::gamma_value::value_type>(
			0.01));

	switch(
		_color_type
	)
	{
	case PNG_COLOR_TYPE_GRAY:
		if(
			_bit_depth == 8
		)
			return sge::image::color::format::l8;
		break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		if(
			_bit_depth == 8
		)
			return sge::image::color::format::la8;
		break;
	case PNG_COLOR_TYPE_PALETTE:
		break;
	case PNG_COLOR_TYPE_RGB:
		if(
			_bit_depth == 8
		)
			return sge::image::color::format::srgb8;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		if(
			_bit_depth == 8
		)
			return sge::image::color::format::srgba8;
		break;
	}

	return sge::image::color::format::size;
}
