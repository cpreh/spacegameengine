/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/libpng/expected_gamma.hpp>
#include <sge/libpng/format.hpp>
#include <sge/libpng/gamma.hpp>
#include <sge/libpng/make_format.hpp>
#include <sge/libpng/optional_format.hpp>
#include <sge/libpng/png.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/diff.hpp>


sge::libpng::optional_format
sge::libpng::make_format(
	png_byte const _color_type,
	png_byte const _bit_depth,
	sge::libpng::gamma const _gamma
)
{
	// For now, we assume that all png images have a gamma of 2.2 (or
	// 0.45455 as a reciprocal), which indicates sRGB. If we have
	// sRGB, we return the corresponding format. The gamma value,
	// however, could be off, in which case we have to look further
	// into it and maybe return a different color format.
	FCPPT_ASSERT_PRE(
		fcppt::math::diff(
			_gamma.get(),
			sge::libpng::expected_gamma().get()
		)
		<
		fcppt::literal<
			sge::libpng::gamma::value_type
		>(
			0.01
		)
	);

	if(
		_bit_depth
		!=
		8
	)
		return
			sge::libpng::optional_format();

	switch(
		_color_type
	)
	{
	case PNG_COLOR_TYPE_GRAY:
		return
			sge::libpng::optional_format(
				sge::libpng::format::l8
			);
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		return
			sge::libpng::optional_format(
				sge::libpng::format::la8
			);
	case PNG_COLOR_TYPE_PALETTE:
		break;
	case PNG_COLOR_TYPE_RGB:
		return
			sge::libpng::optional_format(
				sge::libpng::format::srgb8
			);
	case PNG_COLOR_TYPE_RGB_ALPHA:
		return
			sge::libpng::optional_format(
				sge::libpng::format::srgba8
			);
	}

	return
		sge::libpng::optional_format();
}
