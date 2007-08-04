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


#include <boost/array.hpp>
#include "../../raw_vector.hpp"
#include "../../texture/rect_fragmented_texture.hpp"
#include "../../renderer/transform.hpp"
#include "../font_drawer_3d.hpp"

#include <iostream>

sge::font_drawer_3d::font_drawer_3d(const renderer_ptr rend)
: rend(rend),
  tex_map(new texture_map(rend, new rect_fragmented_texture(rend))),
  sys(rend, tex_map)
{}

void sge::font_drawer_3d::begin_rendering(const size_type buffer_chars)
{
	sprites.clear();
	sprites.reserve(buffer_chars);
}

void sge::font_drawer_3d::draw_char(const font_char ch, const font_rect fr, const font_color* const data)
{
	boost::array<char, sizeof(font_char)+1> char_str;
	for(std::size_t i = 0; i < sizeof(font_char); ++i)
		char_str[i] = *(reinterpret_cast<const char*>(&ch) + i);
	char_str[sizeof(font_char)] = 0;

	const std::string tex_name(char_str.data());
	if(!tex_map->has_texture(tex_name))
	{
		const texture::size_type raw_size = fr.width() * fr.height();
		raw_vector<color> expanded(raw_size);
		for(texture::size_type i = 0; i < raw_size; ++i)
		{
			const color_element elem = data[i];
			expanded[i] = elem ? make_color(elem, elem, elem, 255) : 0;
		}
		tex_map->add_texture(expanded.data(), fr.width(), fr.height(), tex_name);
	}

	const sprite::point sprite_pos = pixel_pos_to_2d<sprite::point>(fr.pos(), rend->screen_size());
	const sprite::dim sprite_sz = pixel_pos_to_2d<sprite::dim>(pixel_pos_t(fr.width(), fr.height()), rend->screen_size());
	sprites.push_back(sprite(sys, sprite_pos, sprite_sz, tex_name, colors::white));
}

void sge::font_drawer_3d::end_rendering()
{
	sys.render();
}
