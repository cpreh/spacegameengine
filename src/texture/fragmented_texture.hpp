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


#ifndef SGE_FRAGMENTED_TEXTURE_HPP_INCLUDED
#define SGE_FRAGMENTED_TEXTURE_HPP_INCLUDED

#include "../shared_ptr.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/renderer.hpp"
#include "virtual_texture.hpp"

namespace sge
{

class fragmented_texture {
public:
	virtual virtual_texture_ptr consume_fragments(texture::size_type w, texture::size_type h) = 0;
	virtual void return_fragments(const virtual_texture&) = 0;
	virtual texture_ptr get_texture() const = 0;
	virtual fragmented_texture* clone() const = 0;
	virtual ~fragmented_texture(){}
};

typedef shared_ptr<fragmented_texture> fragmented_texture_ptr;

}

#endif
