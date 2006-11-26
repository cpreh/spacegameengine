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


#include "../../../raw_vector.hpp"
#include "../../../renderer/transform.hpp"
#include "../font_impl.hpp"
#include FT_GLYPH_H

namespace {
	struct glyph_ptr {
		glyph_ptr(FT_Glyph& g) : g(g) {}
		~glyph_ptr() { FT_Done_Glyph(g); }
	private:
		FT_Glyph& g;
	};
	const sge::texture::size_type tex_size = 512; // TODO: let the driver determine the best texture size
}

sge::ft::font_impl::font_impl(library& lib, const renderer_ptr r, const std::string& font_name, const unsigned quality_in_pixel, const font_weight weight)
: r(r), quality_in_pixel(quality_in_pixel), cur_tex(r->create_texture(0,tex_size,tex_size)), cur_x(0), cur_y(0)
{
	FT_Face face;
	if(FT_New_Face(lib.impl, font_name.c_str(), 0, &face))
		throw std::runtime_error(std::string("FT_New_Face() failed for font: ") += font_name);
	_face.reset(new face_guard(face));

	if(FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
		throw std::runtime_error("No Unicode code map found!");

	if(FT_Set_Pixel_Sizes(face,0,quality_in_pixel))
		throw std::runtime_error("FT_Set_Pixel_Sizes() failed");

	pixel_size = (*_face.get())->height >> 6;
}

const sge::font_entity& sge::ft::font_impl::load_char(const font_char c)
{
	font_entity& entity = buffer[c];
	if(entity.tex)
		return entity;

	if(FT_Load_Char(_face->impl, c /* FT_Get_Char_Index(_face->impl, c)*/, FT_LOAD_DEFAULT))
		throw std::runtime_error("FT_Load_Glyph() failed");

	FT_Glyph glyph;
	if(FT_Get_Glyph((*_face.get())->glyph,&glyph))
		throw std::runtime_error("FT_Get_Glyph() failed");
	glyph_ptr _glyph_gurad(glyph);

	if(FT_Glyph_To_Bitmap(&glyph,FT_RENDER_MODE_NORMAL,0,true))
		throw std::runtime_error("FT_Glyph_To_Bitmap() failed");
		
	FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(glyph);
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	if(cur_x + bitmap.width >= cur_tex->width())
	{
		cur_x = 0;
		cur_y += pixel_size + 1;
	}
	if(cur_y + pixel_size >= cur_tex->height())
	{
		textures.push_back(cur_tex);
		cur_tex = r->create_texture(0, tex_size, tex_size);
		cur_y = 0;
		cur_x = 0;
	}

	const lock_rect lrect(lock_rect::point_type(cur_x, cur_y), lock_rect::dim_type(bitmap.width, bitmap.rows));
	
	entity.rect = tex_size_to_space_rect(lrect, cur_tex->width(), cur_tex->height());
	entity.tex = cur_tex;
	entity.left = font_unit(bitmap_glyph->left) / pixel_size;
	entity.top = font_unit(quality_in_pixel - bitmap_glyph->top) / pixel_size; // FIXME
	entity.x_advance = font_unit((*_face.get())->glyph->advance.x >> 6) / pixel_size;
	entity.v_scale = font_unit(bitmap.rows) / pixel_size;
	entity.h_scale = font_unit(bitmap.width) / pixel_size;

	raw_vector<color> expanded(bitmap.width * bitmap.rows);
	const unsigned char* data = bitmap.buffer;
	for(int y = 0; y < bitmap.rows; ++y, data += bitmap.pitch)
		for(int x = 0; x < bitmap.width; ++x)
		{
			const unsigned char code = *(data + x);
			expanded.at(y*bitmap.width+x) = code ? rgba(code,code,code,255) : colors::transparent;
		}

	cur_tex->set_data(expanded.data(),&lrect);
	cur_x += bitmap.width + 1;

	return entity;
}

unsigned sge::ft::font_impl::optimal_height_base() const
{
	return pixel_size;
}
