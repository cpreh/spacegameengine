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


#ifndef SGE_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_CUBE_TEXTURE_HPP_INCLUDED

#include "./texture_base.hpp"
#include <boost/array.hpp>

namespace sge
{

enum cube_side {
	CS_Front,
	CS_Back,
	CS_Left,
	CS_Right,
	CS_Top,
	CS_Bottom
};

template<typename BitDepth>
class basic_cube_texture : public basic_texture_base<BitDepth> {
public:
	typedef basic_texture_base<BitDepth> base;
	typedef typename base::const_pointer const_pointer;
	virtual void set_data(cube_side side, const_pointer p, const lock_rect* r = 0) = 0;
};

typedef basic_cube_texture<BitDepth32> cube_texture;
typedef shared_ptr<cube_texture> cube_texture_ptr;
typedef boost::array<cube_texture::const_pointer,6> cube_side_src_array;

}

#endif
