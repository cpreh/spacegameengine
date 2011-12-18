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


#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/const_image_view.hpp>
#include <sge/font/exception.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/unit.hpp>
#include <sge/freetype/freetype.hpp>
#include <sge/freetype/face.hpp>
#include <sge/freetype/char_metric.hpp>
#include <sge/freetype/glyph.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/log/global.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::freetype::char_metric::char_metric(
	freetype::face &_face,
	sge::charconv::system &_conv_system,
	font::char_type const _ch
)
:
	buffer_(),
	offset_(),
	x_advance_()
{
	// TODO: we could implement a convert function that does this on chars
	typedef sge::charconv::string_type<
		sge::charconv::encoding::utf32
	>::type utf32_string;

	utf32_string const converted_string(
		sge::charconv::convert<
			sge::charconv::encoding::utf32,
			sge::charconv::encoding::wchar
		>(
			_conv_system,
			std::basic_string<
				font::char_type
			>(
				1u,
				_ch
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		converted_string.size() == 1u
	);

	if(
		::FT_Load_Char(
			_face.get(),
			converted_string[0],
			FT_LOAD_DEFAULT
		)
	)
		throw sge::font::exception(
			FCPPT_TEXT("FT_Load_Glyph() failed!")
		);

	freetype::glyph glyph(
		_face
	);

	FT_BitmapGlyph const bmp_glyph(
		glyph.bitmap_glyph()
	);

	FT_Bitmap &bitmap(
		bmp_glyph->bitmap
	);

	offset_.x() = bmp_glyph->left;

	offset_.y() = static_cast<font::unit>(_face->size->metrics.ascender / 64 - bmp_glyph->top);

	x_advance_ = static_cast<font::unit>(_face->glyph->advance.x / 64);

	// FIXME: fix offsets and maybe those warnings
	if(offset_.x() < 0)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("x offset of character '")
				<< _ch
				<< FCPPT_TEXT("' is ")
				<< offset_.x()
				<< FCPPT_TEXT('!')
		);

	if(offset_.y() < 0)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("y offset of character '")
				<< _ch
				<< FCPPT_TEXT("' is ")
				<< offset_.y()
				<< FCPPT_TEXT('!')
		);

	// FIXME
	if(
		bitmap.pitch < 0
	)
		throw sge::exception(
			FCPPT_TEXT("FIXME: bitmap pitch < 0, case not handled!")
		);

	sge::image2d::dim const dim(
		static_cast<
			sge::image2d::dim::value_type
		>(
			bitmap.width
		),
		static_cast<
			sge::image2d::dim::value_type
		>(
			bitmap.rows
		)
	);

	buffer_ = buffer_type(
		dim
	);

	sge::image2d::algorithm::copy_and_convert(
		sge::image2d::view::make_const(
			static_cast<
				unsigned char const *
			>(
				bitmap.buffer
			),
			dim,
			sge::image::color::format::a8,
			sge::image2d::view::optional_pitch(
				static_cast<
					sge::image2d::pitch
				>(
					bitmap.pitch - bitmap.width
				)
			)
		),
		sge::image2d::view::object(
			buffer_.wrapped_view()
		),
		sge::image::algorithm::may_overlap::no
	);
}

sge::freetype::char_metric::~char_metric()
{
}

sge::font::pos const
sge::freetype::char_metric::offset() const
{
	return offset_;
}

sge::font::const_image_view const
sge::freetype::char_metric::pixmap() const
{
	return
		sge::font::const_image_view(
			buffer_.wrapped_view()
		);
}

sge::font::unit
sge::freetype::char_metric::x_advance() const
{
	return x_advance_;
}
