#include <stdexcept>
#include "../../../core/renderer/renderer_types.hpp"
#include "../../../core/renderer/renderer.hpp"
#include "../../../core/renderer/texture_helper.hpp"
#include "../../../core/main/raw_vector.hpp"
#include "../font_system.hpp"
#include FT_GLYPH_H

namespace {
	struct face_ptr {
		face_ptr(FT_Face& f) : f(f) {}
		~face_ptr() { FT_Done_Face(f); }
	private:
		FT_Face& f;
	};
	struct glyph_ptr {
		glyph_ptr(FT_Glyph& g) : g(g) {}
		~glyph_ptr() { FT_Done_Glyph(g); }
	private:
		FT_Glyph& g;
	};
}

sge::ft::font_system::font_system()
{
	if(FT_Init_FreeType(&library))
		throw std::runtime_error("FT_Init_FreeType() failed");
}

sge::ft::font_system::~font_system()
{
	FT_Done_FreeType(library);
}

// TODO: portabel in case of sizeof(int)==1
sge::font_information sge::ft::font_system::create_font(const renderer_ptr r, const std::string& font_name, const bool italic, const font_weight weight, const text_unit height, const std::locale& loc)
{
	font_information info;

	const texture::size_type tex_size = 512;

	FT_Face face;
	if(FT_New_Face(library,font_name.c_str(),0,&face))
		throw std::runtime_error(std::string("FT_New_Face() failed for font: ") += font_name);
	face_ptr _face_guard(face);

	const unsigned pixel_size = 32;
	if(FT_Set_Pixel_Sizes(face,0,pixel_size))
		throw std::runtime_error("FT_Set_Pixel_Sizes() failed");
	info.font_height = text_unit(pixel_size) / tex_size;

	const char min = std::numeric_limits<char>::min(),
	           max = std::numeric_limits<char>::max();
	info.positions.reserve(unsigned(max)-min);

	info.tex = r->create_texture(0,tex_size,tex_size);

	unsigned cur_x = 0, cur_y = 0;
	int max_height = 0;
	for(int i = min; i <= max; ++i)
	{
		const char ch(i);
		if(!std::isprint(ch,loc) || FT_Load_Char(face,ch,FT_LOAD_DEFAULT))
		{
			info.positions.push_back(font_information::position());
			continue;
		}

		FT_Glyph glyph;
		if(FT_Get_Glyph(face->glyph,&glyph))
			throw std::runtime_error("FT_Get_Glyph() failed");
		glyph_ptr _glyph_gurad(glyph);

		if(FT_Glyph_To_Bitmap(&glyph,FT_RENDER_MODE_NORMAL,0,true))
			throw std::runtime_error("FT_Glyph_To_Bitmap() failed");
		
		FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(glyph);

		FT_Bitmap& bitmap = bitmap_glyph->bitmap;
		const int width = bitmap.width, height = bitmap.rows;
		max_height = std::max(height,max_height);
		if(cur_x + width >= tex_size)
		{
			cur_x = 0;
			cur_y += max_height;
			max_height = 0;
		}
		if(cur_y + height >= tex_size)
			throw std::runtime_error("Problem with freetype font: texture too small!");

		const lock_rect lrect(lock_rect::point_type(cur_x, cur_y), lock_rect::dim_type(width, height));

		info.positions.push_back(
				font_information::position(to_coordinate_rect(lrect, info.tex),
				text_unit(pixel_size-bitmap_glyph->top) / pixel_size));

		raw_vector<color> expanded(width*height);
		for(int y = 0; y < height; ++y)
			for(int x = 0; x < width; ++x)
				expanded[y*width+x] = y < bitmap.rows && x < bitmap.width ?
					(bitmap.buffer[y*bitmap.width+x] ? colors::white : colors::transparent) : 0;

		info.tex->set_data(expanded.data(),&lrect);
		cur_x += width;
	}
	return info;
}
