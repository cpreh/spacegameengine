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


#ifndef SGE_SPRITE_DETAILS_HPP_INCLUDED
#define SGE_SPRITE_DETAILS_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include "../math/rect.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/renderer.hpp"
#include "../types.hpp"
#include "../shared_ptr.hpp"
#include "../bsp_tree.hpp"

namespace sge
{

class fragmented_texture;

class virtual_texture : boost::noncopyable {
public:
	virtual_texture(const lock_rect&, fragmented_texture*);
	~virtual_texture();
	lock_rect area() const { return _area; }
	texture_ptr my_texture() const;
	void set_data(texture::const_pointer src);
private:
	lock_rect _area;
	fragmented_texture* fragment;
};

typedef shared_ptr<virtual_texture> virtual_texture_ptr;
typedef shared_ptr<const virtual_texture> const_virtual_texture_ptr;

class fragmented_texture : boost::noncopyable {
public:
	fragmented_texture(renderer_ptr r, texture::size_type texsize);
	virtual_texture_ptr consume_fragments(texture::size_type w, texture::size_type h);
	void return_fragments(const virtual_texture&);
	texture_ptr get_texture() const { return tex; }
private:
	typedef bsp_tree<texture::size_type> bsp_type;
	bsp_type bsp;
	texture_ptr tex;
};

}

#endif
