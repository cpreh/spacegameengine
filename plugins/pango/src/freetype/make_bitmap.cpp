/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/exception.hpp>
#include <sge/font/view.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/view/data.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/pitch.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/pango/freetype/make_bitmap.hpp>
#include <sge/pango/freetype/pixel_mode.hpp>
#include <mizuiro/image/view_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ft2build.h>
#include FT_BITMAP_H
#include FT_IMAGE_H
#include <fcppt/config/external_end.hpp>


FT_Bitmap
sge::pango::freetype::make_bitmap(
	sge::font::view const &_view
)
{
	sge::image2d::dim const size{
		sge::image2d::view::size(
			_view
		)
	};

	unsigned const width(
		fcppt::cast::size<
			unsigned
		>(
			size.w()
		)
	);

	unsigned const height(
		fcppt::cast::size<
			unsigned
		>(
			size.h()
		)
	);

	FT_Bitmap bitmap;

	FT_Bitmap_Init(
		&bitmap
	);

	bitmap.rows =
		height;

	bitmap.width =
		width;

	int const pitch(
		fcppt::cast::size<
			int
		>(
			sge::image2d::view::pitch(
				_view
			).w()
		)
	);

	// For FreeType, pitch means the distance from the start of one line to
	// the start of the next line. If the pitch is positive, the image goes
	// downwards. Because mizuiro doesn't include the width in this case,
	// we have to add it. If the pitch is negative, mizuiro already
	// includes the width (as a negative component), so add it back.
	bitmap.pitch =
		pitch
		+
		fcppt::cast::to_signed(
			width
		);

	bitmap.buffer =
		sge::image2d::view::data(
			_view
		);

	bitmap.num_grays =
		256;

	sge::image::color::format const format{
		sge::image2d::view::format(
			_view
		)
	};

	bitmap.pixel_mode =
		fcppt::optional::to_exception(
			sge::pango::freetype::pixel_mode(
				format
			),
			[
				format
			]{
				return
					sge::font::exception{
						FCPPT_TEXT("Unsupported image format ")
						+
						sge::image::color::format_to_string(
							format
						)
					};
			}
		);

	return
		bitmap;
}
