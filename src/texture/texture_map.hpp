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


#ifndef SGE_TEXTURE_MAP_HPP_INCLUDED
#define SGE_TEXTURE_MAP_HPP_INCLUDED

#include <string>
#include <map>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include "manager.hpp"
#include "../renderer/renderer.hpp"
#include "../image/image.hpp"
#include "../shared_ptr.hpp"

namespace sge
{

class fragmented_texture;

class texture_map : boost::noncopyable {
public:
	typedef boost::function<bool (texture_map&,const std::string&)> handler_function;

	texture_map(renderer_ptr rend, const fragmented_texture* proto, handler_function not_found_handler = 0);
	bool add_texture(texture::const_pointer src, texture::size_type w, texture::size_type h, const std::string& name);
	bool add_texture(image_ptr im, const std::string& name, bool scale);
	bool add_texture(texture_ptr tex, const std::string& name);
	bool remove_texture(const std::string& name);
	
	virtual_texture_ptr vtexture(const std::string&);

	static const char* const no_texture;
private:
	renderer_ptr rend;
	handler_function texture_not_present_handler;
	texture_manager tex_man;
	
	typedef std::map<std::string, virtual_texture_ptr> virtual_texture_map;
	virtual_texture_map virtual_textures;
};

typedef shared_ptr<texture_map> texture_map_ptr;

}

#endif
