/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/font/font_drawer_3d.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/texture/rect_fragmented_texture.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/sprite/system_impl.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/renderer/colors.hpp>

sge::font_drawer_3d::font_drawer_3d(const renderer_ptr rend, const color col)
: rend(rend),
  col(col),
  texman(rend, default_texture_creator<rect_fragmented_texture>(rend, linear_filter)),
  sys(rend)
{}

void sge::font_drawer_3d::begin_rendering(const size_type buffer_chars, const font_dim)
{
	sprites.clear();
	sprites.reserve(buffer_chars);
}

void sge::font_drawer_3d::draw_char(const font_char ch, const font_rect fr, const font_color* const data)
{
	texture_map::const_iterator it = textures.find(ch);
	if(it == textures.end())
	{
		const texture::size_type raw_size = fr.w() * fr.h();
		raw_vector<color> expanded(raw_size);
		for(texture::size_type i = 0; i < raw_size; ++i)
		{
			const color_element elem = data[i];
			expanded[i] = elem ? make_color(elem, elem, elem, 255) : 0;
		}
		textures.insert(
			std::make_pair(
				ch,
				texman.add_texture(
					expanded.data(),
					texture::dim_type(
						fr.w(),
						fr.h()))));
		it = textures.find(ch);
	}

	sprites.push_back(
		sprite::object(
			fr.pos(),
			it->second,
			fr.size(),
			col));
}

void sge::font_drawer_3d::end_rendering()
{
	sys.render(sprites.begin(), sprites.end());
}

void sge::font_drawer_3d::set_color(const color new_color)
{
	col = new_color;
}
