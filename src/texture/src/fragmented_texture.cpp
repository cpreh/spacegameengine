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


#include "../fragmented_texture.hpp"

sge::fragmented_texture::fragmented_texture(const renderer_ptr r, const texture::size_type texsize/*, const texture_placement_system_ptr strategy*/)
 : tex(r->create_texture(0, texsize, texsize)),
   bsp(bsp_tree::dim_type(r->caps().max_tex_size,r->caps().max_tex_size))
//   strategy(strategy)
{}

sge::virtual_texture_ptr sge::fragmented_texture::consume_fragments(const texture::size_type w, const texture::size_type h)
{
/*	const texture_placement_system::ret_type t = strategy->insert(texture_placement_system::dim_type(w,h));
	if(t.second == false)
		return virtual_texture_ptr();
	return virtual_texture_ptr(new virtual_texture(t.first, this));*/

	bsp_tree::iterator it = bsp.insert(bsp_tree::dim_type(w,h));
	if(it == bsp.end())
		return virtual_texture_ptr();
	return virtual_texture_ptr(new virtual_texture(*it, this));
}

void sge::fragmented_texture::return_fragments(const virtual_texture& t)
{
//	strategy->erase(t.area());
	bsp.erase(bsp.find(t.area()));
}

sge::texture_ptr sge::fragmented_texture::get_texture() const
{
	return tex;
}
