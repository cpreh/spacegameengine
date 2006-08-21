#include "../../../core/main/raw_vector.hpp"
#include "../../../core/renderer/texture_helper.hpp"
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

sge::ft::font_impl::font_impl(library& lib, const renderer_ptr r, const std::string& font_name, const font_weight weight)
: r(r), pixel_size(32), cur_tex(r->create_texture(0,tex_size,tex_size)), cur_x(0), cur_y(0) // TODO: some option for text quality
{
	FT_Face face;
	if(FT_New_Face(lib.impl, font_name.c_str(), 0, &face))
		throw std::runtime_error(std::string("FT_New_Face() failed for font: ") += font_name);
	_face.reset(new face_guard(face));

	if(FT_Set_Pixel_Sizes(face,0,pixel_size))
		throw std::runtime_error("FT_Set_Pixel_Sizes() failed");
}

sge::font_char_rect sge::ft::font_impl::load_char(const font_char c)
{
	const std::size_t index = c-CHAR_MIN;
	if(buffer[index].tex)
		return buffer[index];
	
	if(FT_Load_Glyph( _face->impl, FT_Get_Char_Index(_face->impl, c), FT_LOAD_DEFAULT))
		throw std::runtime_error("FT_Load_Glyph() failed");

	FT_Glyph glyph;
	if(FT_Get_Glyph(_face->impl->glyph,&glyph))
		throw std::runtime_error("FT_Get_Glyph() failed");
	glyph_ptr _glyph_gurad(glyph);

	if(FT_Glyph_To_Bitmap(&glyph,FT_RENDER_MODE_NORMAL,0,true))
		throw std::runtime_error("FT_Glyph_To_Bitmap() failed");
		
	FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(glyph);
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	const int width = bitmap.width, height = bitmap.rows;

	if(cur_x + width >= cur_tex->width())
	{
		cur_x = 0;
		cur_y += pixel_size;
	}
	if(cur_y + pixel_size >= cur_tex->height())
	{
		textures.push_back(cur_tex);
		cur_tex = r->create_texture(0, tex_size, tex_size);
		cur_y = 0;
	}

	const lock_rect lrect(lock_rect::point_type(cur_x, cur_y), lock_rect::dim_type(width, height));
	
	font_char_rect& rect = buffer[index];
	rect.tex = cur_tex;
	rect.rect = to_coordinate_rect(lrect, cur_tex);
	rect.top = font_unit(pixel_size - bitmap_glyph->top) / pixel_size;

	raw_vector<color> expanded(width*height);
	for(int y = 0; y < height; ++y)
		for(int x = 0; x < width; ++x)
			expanded[y*width+x] = y < bitmap.rows && x < bitmap.width ?
				(bitmap.buffer[y*bitmap.width+x] ? colors::white : colors::transparent) : 0;

	cur_tex->set_data(expanded.data(),&lrect);
	cur_x += width;

	return buffer[index];
}

unsigned sge::ft::font_impl::optimal_height_base() const
{
	return pixel_size;
}
