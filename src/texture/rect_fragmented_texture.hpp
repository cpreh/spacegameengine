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


#ifndef SGE_RECT_FRAGMENTED_TEXTURE_HPP_INCLUDED
#define SGE_RECT_FRAGMENTED_TEXTURE_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include "fragmented_texture.hpp"

namespace sge
{

// this is just a temporary hack
class rect_fragmented_texture : public fragmented_texture {
public:
	rect_fragmented_texture(renderer_ptr rend);
	virtual_texture_ptr consume_fragments(texture::size_type w, texture::size_type h);
	void return_fragments(const virtual_texture&);
	texture_ptr get_texture() const;
	fragmented_texture* clone() const;
private:
	renderer_ptr       rend;
	texture::size_type cur_x,
	                   cur_y,
	                   cur_height;
	texture_ptr        tex;
};

}

#endif
