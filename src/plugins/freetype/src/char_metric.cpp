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


#include "../freetype.hpp"
#include "../face.hpp"
#include "../glyph.hpp"
#include "../char_metric.hpp"
#include <sge/exception.hpp>
#include <sge/raw_vector_impl.hpp>
#include <cstring>

sge::ft::char_metric::char_metric(
	face& face_,
	const char_type ch,
	const font::unit pixel_size)
{
	if(FT_Load_Char(face_.get(), ch, FT_LOAD_DEFAULT))
		throw exception(SGE_TEXT("FT_Load_Glyph() failed!"));

	glyph glyph_(face_);
	FT_BitmapGlyph bmp_glyph = glyph_.bitmap_glyph();

	FT_Bitmap& bitmap = bmp_glyph->bitmap;

	width_ = bitmap.width;
	height_ = bitmap.rows;
	left_ = bmp_glyph->left;
	top_ = static_cast<int>(pixel_size) - bmp_glyph->top + face_->descender / 64;
	x_advance_ = static_cast<font::unit>(face_->glyph->advance.x / 64);

	if(bitmap.width == 0 || bitmap.rows == 0)
		return;

	buffer.resize_uninitialized(bitmap.width * bitmap.rows);
	const unsigned char* data = bitmap.buffer;
	for(int y = 0; y < bitmap.rows; ++y, data += bitmap.pitch)
		std::memcpy(buffer.data() + y * width(), data, width());
}

const sge::font::color* sge::ft::char_metric::pixmap() const
{
	return buffer.data();
}

sge::font::unit sge::ft::char_metric::width() const
{
	return width_;
}

sge::font::unit sge::ft::char_metric::height() const
{
	return height_;
}

sge::font::unit sge::ft::char_metric::left() const
{
	return left_;
}

sge::font::unit sge::ft::char_metric::top() const
{
	return top_;
}

sge::font::unit sge::ft::char_metric::x_advance() const
{
	return x_advance_;
}
