#ifndef SGE_FREETYPE_FONT_IMPL_HPP_INCLUDED
#define SGE_FREETYPE_FONT_IMPL_HPP_INCLUDED

#include <climits>
#include <memory>
#include <vector>
#include <boost/array.hpp>
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
	font_impl(library& lib, renderer_ptr r, const std::string& font_name, unsigned quality_in_pixel, font_weight weight);
	font_entity load_char(font_char c);
	unsigned optimal_height_base() const;
private:
	struct face_guard {
		face_guard(FT_Face f) : impl(f) {}
		~face_guard() { FT_Done_Face(impl); }
		FT_Face operator->() const { return impl; }
		FT_Face impl;
	};

	renderer_ptr r;
	unsigned quality_in_pixel;
	texture_ptr cur_tex;
	texture::size_type cur_x, cur_y;

	std::auto_ptr<face_guard> _face;
	unsigned pixel_size;
	typedef boost::array<font_entity, UCHAR_MAX> buffer_type;
	buffer_type buffer;
	typedef std::vector<texture_ptr> texture_array;
	texture_array textures;
};

}
}

#endif
