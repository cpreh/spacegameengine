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


#include "../bsp_fragmented_texture.hpp"

sge::bsp_fragmented_texture::bsp_fragmented_texture(const renderer_ptr rend)
 : rend(rend),
   bsp(bsp_type::dim_type(rend->caps().max_tex_size,rend->caps().max_tex_size))
{}

sge::virtual_texture_ptr sge::bsp_fragmented_texture::consume_fragments(const texture::size_type w, const texture::size_type h)
{
	if(!tex)
		tex = rend->create_texture(0, rend->caps().max_tex_size, rend->caps().max_tex_size, linear_filter);
	const bsp_type::iterator it = bsp.insert(bsp_type::dim_type(w,h));
	if(it == bsp.end())
		return virtual_texture_ptr();
	return virtual_texture_ptr(new virtual_texture(*it, this));
}

void sge::bsp_fragmented_texture::return_fragments(const virtual_texture& t)
{
	bsp.erase(bsp.find(t.area()));
}

sge::texture_ptr sge::bsp_fragmented_texture::get_texture() const
{
	return tex;
}

sge::fragmented_texture* sge::bsp_fragmented_texture::clone() const
{
	return new bsp_fragmented_texture(rend);
}
