#include <stdexcept>
#include "../font_system.hpp"

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

sge::font_information sge::ft::font_system::create_font(const renderer_ptr r, const std::string& font_name, const font_weight weight)
{
	return font_impl_ptr(new font_impl(r, font_name, weight));
}


