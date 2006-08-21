#ifndef SGE_FREETYPE_FONT_IMPL_HPP_INCLUDED
#define SGE_FREETYPE_FONT_IMPL_HPP_INCLUDED

#include <climits>
#include <memory>
#include <vector>
#include "../../core/font/font_impl.hpp"
#include "../../core/renderer/renderer.hpp"
#include "../../core/renderer/texture.hpp"
#include "./library.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace sge
{
namespace ft
{

class font_impl : public sge::font_impl {
public:
	font_impl(library& lib, renderer_ptr r, const std::string& font_name, const font_weight weight);
	font_char_rect load_char(font_char c);
	unsigned optimal_height_base() const;
private:
	struct face_guard {
		face_guard(FT_Face f) : impl(f) {}
		~face_guard() { FT_Done_Face(impl); }
		FT_Face impl;
	};

	renderer_ptr r;
	std::auto_ptr<face_guard> _face;
	unsigned pixel_size;
	texture_ptr cur_tex;
	texture::size_type cur_x, cur_y;

	font_char_rect buffer[UCHAR_MAX];
	typedef std::vector<texture_ptr> texture_array;
	texture_array textures;
};

}
}

#endif
