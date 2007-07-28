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


#include <iostream>
#include "../../../raw_vector.hpp"
#include "../../../renderer/transform.hpp"
#include "../font_metrics.hpp"
#include "../glyph.hpp"

sge::ft::font_metrics::font_metrics(library& lib, const renderer_ptr r, const std::string& font_name, const unsigned quality_in_pixel)
: r(r),
  cur_tex(r->create_texture(0, r->caps().max_tex_size, r->caps().max_tex_size, linear_filter)), // TODO
  cur_x(0),
  cur_y(0),
  _face(lib, font_name)
{
	if(FT_Select_Charmap(_face.get(), FT_ENCODING_UNICODE) != 0)
		throw std::runtime_error("No Unicode code map found!");

	if(FT_Set_Pixel_Sizes(_face.get(), 0, quality_in_pixel))
		throw std::runtime_error("FT_Set_Pixel_Sizes() failed");

	pixel_size =  _face->ascender / 64 - _face->descender / 64;
}

const sge::font_entity& sge::ft::font_metrics::load_char(const font_char c)
{
	font_entity& entity = buffer[c];
	if(entity.tex)
		return entity;

	if(FT_Load_Char(_face.get(), c, FT_LOAD_DEFAULT))
		throw std::runtime_error("FT_Load_Glyph() failed");

	glyph _glyph(_face);
	FT_BitmapGlyph bmp_glyph = _glyph.bitmap_glyph();

	FT_Bitmap& bitmap = bmp_glyph->bitmap;

	if(cur_x + bitmap.width >= cur_tex->width())
	{
		cur_x = 0;
		cur_y += pixel_size + 1;
	}
	if(cur_y + bitmap.rows >= cur_tex->height())
	{
		textures.push_back(cur_tex);
		cur_tex = r->create_texture(0, r->caps().max_tex_size, r->caps().max_tex_size, linear_filter); // TODO
		cur_y = 0;
		cur_x = 0;
	}

	const lock_rect lrect(lock_rect::point_type(cur_x, cur_y), lock_rect::dim_type(bitmap.width, bitmap.rows));

	entity.rect = tex_size_to_space_rect(lrect, cur_tex->width(), cur_tex->height());
	entity.tex = cur_tex;
	entity.left = font_unit(bmp_glyph->left) / pixel_size;
	entity.top = font_unit(static_cast<int>(pixel_size) - bmp_glyph->top + (_face->descender / 64)) / pixel_size;
	entity.x_advance = font_unit(_face->glyph->advance.x >> 6) / pixel_size;
	entity.v_scale = font_unit(bitmap.rows) / pixel_size;
	entity.h_scale = font_unit(bitmap.width) / pixel_size;

	raw_vector<color> expanded(bitmap.width * bitmap.rows);
	const unsigned char* data = bitmap.buffer;
	for(int y = 0; y < bitmap.rows; ++y, data += bitmap.pitch)
		for(int x = 0; x < bitmap.width; ++x)
		{
			const unsigned char code = *(data + x);
			expanded.at(y*bitmap.width+x) = code ? make_color(code,code,code,255) : colors::transparent;
		}

	cur_tex->set_data(expanded.data(),&lrect);
	cur_x += bitmap.width + 1;

	return entity;
}

unsigned sge::ft::font_metrics::optimal_height_base() const
{
	return pixel_size;
}
