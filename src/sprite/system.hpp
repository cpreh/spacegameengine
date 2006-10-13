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


#ifndef SGE_SPRITE_SYSTEM_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_HPP_INCLUDED

#include <stdexcept>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include "./types.hpp"
#include "./sprite.hpp"
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/renderer.hpp"
#include "../image/image.hpp"
#include "../math/matrix4x4.hpp"

namespace sge
{

class sprite_system : boost::noncopyable {
public:
	typedef boost::function<void (const std::string&)> handler_function;
	typedef matrix4x4<space_unit> matrix_type;

	sprite_system(renderer_ptr r, handler_function not_found_handler = 0);
	bool add_texture(texture::const_pointer src, texture::size_type w, texture::size_type h, const std::string& name);
	bool add_texture(image_ptr im, const std::string& name);
	bool remove_texture(const std::string& name);
	void draw();
	void clear();
	void set_parameters();
	void transform(const matrix_type& mat);
	static const char* const no_texture;

	class image_too_big : public std::logic_error {
	public:
		image_too_big() : std::logic_error("image in sprite_system::add_texture is too big") {}
	};
private:
	virtual_texture_ptr vtexture(const std::string&) const;

	void insert_texture(virtual_texture_ptr, texture::const_pointer src, const std::string& name);
	sprite_list::iterator attach(sprite& s);
	void detach(const sprite& s);
	vertex_buffer::size_type free_vb_pos();

	friend class sprite;

	handler_function texture_not_present_handler;
	sprite_list sprites;
	renderer_ptr r;
	texture::size_type texsize;

	typedef shared_ptr<fragmented_texture> fragmented_texture_ptr;
	typedef std::list<fragmented_texture_ptr> fragmented_texture_list;
	fragmented_texture_list fragmented_textures;

	typedef std::map<std::string, virtual_texture_ptr> virtual_texture_map;
	virtual_texture_map virtual_textures;

	vertex_buffer_ptr vb;
	index_buffer_ptr ib;
	typedef std::vector<vertex_buffer::size_type> free_pos_vector;
	free_pos_vector free_pos;

	matrix_type     trans;
};

}

#endif

