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


#include "../manager.hpp"

const sge::texture::size_type texsize = 512; // TODO

sge::texture_manager::texture_manager(const renderer_ptr rend)
 : rend(rend)
{}

sge::virtual_texture_ptr sge::texture_manager::add_texture(const texture::const_pointer src, const texture::size_type w, const texture::size_type h)
{
	for(fragmented_texture_list::iterator it = fragmented_textures.begin(); it != fragmented_textures.end(); ++it)
		if(virtual_texture_ptr p = (*it)->consume_fragments(w,h))
		{
			p->set_data(src);
			return p;
		}
		
	fragmented_textures.push_back(fragmented_texture_ptr(new fragmented_texture(rend, texsize)));
	if(virtual_texture_ptr p = fragmented_textures.back()->consume_fragments(w,h))
	{
		p->set_data(src);
		return p;
	}
	// TODO: ask the driver if a texture this big can be created and do it
	//throw std::runtime_error(std::string("sprite_system::add_texture(): failed to allocate texture \"") += name + "\" (texture may be too big)!");
	// if(r->caps(MAX_TEX_SIZE) >= std::max(w,h))
	
	throw image_too_big();
}

sge::renderer_ptr sge::texture_manager::get_renderer() const
{
	return rend;
}
