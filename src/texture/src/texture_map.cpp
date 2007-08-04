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


#include <cassert>
#include "../texture_map.hpp"

namespace
{

bool default_texture_not_present_handler(sge::texture_map&, const std::string&)
{
	return false;
}

}

sge::texture_map::texture_map(const renderer_ptr rend, const fragmented_texture* const proto, const handler_function handler)
 : rend(rend),
   texture_not_present_handler(handler == 0 ? default_texture_not_present_handler : handler),
   tex_man(rend, proto)
{}

bool sge::texture_map::has_texture(const std::string& name) const
{
	return virtual_textures.find(name) != virtual_textures.end();
}

void sge::texture_map::add_texture(const texture::const_pointer src, const texture::size_type w, const texture::size_type h, const std::string& name)
{
	if(has_texture(name))
		return;

	virtual_textures[name] = tex_man.add_texture(src,w,h);
}

void sge::texture_map::add_texture(const image_ptr im, const std::string& name, const bool scale)
{
	if(has_texture(name))
		return;

	virtual_textures[name] = tex_man.add_texture(im, scale);
}

void sge::texture_map::add_texture(const texture_ptr tex, const std::string& name)
{
	if(has_texture(name))
		return;

	virtual_textures[name] = tex_man.add_texture(tex);
}

void sge::texture_map::remove_texture(const std::string& name)
{
	if(!has_texture(name))
		return;

	virtual_textures.erase(virtual_textures.find(name));
}

sge::virtual_texture_ptr sge::texture_map::vtexture(const std::string& name)
{
	if(name == no_texture)
		return virtual_texture_ptr();
	
	virtual_texture_map::const_iterator it = virtual_textures.find(name);
	if(it == virtual_textures.end())
		if(texture_not_present_handler(*this,name) == false)
			throw std::logic_error(std::string("texture_not_present_handler in texture_map failed for texture \"") += name + "\"!");
		else
			it = virtual_textures.find(name);
	assert(it != virtual_textures.end());
	return it->second;
}

const char* const sge::texture_map::no_texture = "";
