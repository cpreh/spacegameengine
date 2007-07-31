/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../../../exception.hpp"
#include "../freetype.hpp"
#include "../face.hpp"
#include "../glyph.hpp"
#include "../char_metric.hpp"

sge::ft::char_metric::char_metric(face& _face, const font_char ch, const font_unit pixel_size)
{
	if(FT_Load_Char(_face.get(), ch, FT_LOAD_DEFAULT))
		throw exception("FT_Load_Glyph() failed");

	glyph _glyph(_face);
	FT_BitmapGlyph bmp_glyph = _glyph.bitmap_glyph();

	FT_Bitmap& bitmap = bmp_glyph->bitmap;

	width_ = bitmap.width;
	height_ = bitmap.rows;
	left_ = bmp_glyph->left;
	top_ = static_cast<int>(pixel_size) - bmp_glyph->top + _face->descender / 64;
	x_advance_ = _face->glyph->advance.x / 64;
	
	expanded_data.resize(bitmap.width * bitmap.rows);
	const unsigned char* data = bitmap.buffer;
	for(int y = 0; y < bitmap.rows; ++y, data += bitmap.pitch)
		for(int x = 0; x < bitmap.width; ++x)
		{
			const unsigned char code = *(data + x);
			expanded_data.at(y*bitmap.width+x) = code ? make_color(code,code,code,255) : colors::transparent;
		}
}

const sge::color* sge::ft::char_metric::pixmap() const
{
	return expanded_data.data();
}

sge::font_unit sge::ft::char_metric::width() const
{
	return width_;
}

sge::font_unit sge::ft::char_metric::height() const
{
	return height_;
}

sge::font_unit sge::ft::char_metric::left() const
{
	return left_;
}

sge::font_unit sge::ft::char_metric::top() const
{
	return top_;
}

sge::font_unit sge::ft::char_metric::x_advance() const
{
	return x_advance_;
}
