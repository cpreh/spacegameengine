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
#include <sge/image/color/a8_format.hpp>
#include <sge/image2d/view/element_base.hpp>
#include <sge/pango/freetype/make_bitmap.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <mizuiro/image/view_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/variant/to_optional.hpp>
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
	typedef sge::image2d::view::element_base<
		sge::image::color::a8_format,
		mizuiro::nonconst_tag
	>::type a8_view;

	a8_view const &view(
		fcppt::optional::to_exception(
			fcppt::variant::to_optional<
				a8_view
			>(
				_view.get()
			),
			[]{
				return
					sge::font::exception{
						FCPPT_TEXT("Only a8 views are currently supported by sge::pango!")
					};
			}
		)
	);

	unsigned const width(
		fcppt::cast::size<
			unsigned
		>(
			view.size()[0]
		)
	);

	unsigned const height(
		fcppt::cast::size<
			unsigned
		>(
			view.size()[1]
		)
	);

	FT_Bitmap bitmap;

	FT_Bitmap_Init(
		&bitmap
	);

	bitmap.rows = height;

	bitmap.width = width;

	int const pitch(
		fcppt::cast::size<
			int
		>(
			view.pitch()[0]
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

	bitmap.buffer = view.data();

	bitmap.num_grays = 256;

	bitmap.pixel_mode = FT_PIXEL_MODE_GRAY;

	return bitmap;
}
