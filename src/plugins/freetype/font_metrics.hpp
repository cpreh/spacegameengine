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


#ifndef SGE_FT_FONT_METRICS_HPP_INCLUDED
#define SGE_FT_FONT_METRICS_HPP_INCLUDED

#include <vector>
#include <map>
#include "../../font/font_metrics.hpp"
#include "../../renderer/renderer.hpp"
#include "../../renderer/texture.hpp"
#include "./library.hpp"
#include "face.hpp"
#include "freetype.hpp"

namespace sge
{
namespace ft
{

class font_metrics : public sge::font_metrics {
public:
	font_metrics(library& lib, renderer_ptr r, const std::string& font_name, unsigned quality_in_pixel);
	const font_entity& load_char(font_char c);
	unsigned optimal_height_base() const;
private:
	renderer_ptr r;
	texture_ptr cur_tex;
	texture::size_type cur_x, cur_y;
	face _face;

	unsigned pixel_size;
	typedef std::map<font_char, font_entity> buffer_type;
	buffer_type buffer;
	typedef std::vector<texture_ptr> texture_array;
	texture_array textures;
};

}
}

#endif
