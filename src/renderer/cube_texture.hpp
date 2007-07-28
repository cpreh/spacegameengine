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

#include <boost/array.hpp>
#include "texture_base.hpp"
#include "types.hpp"

namespace sge
{

namespace cube_side
{
	enum type {
		front,
		back,
		left,
		right,
		top,
		bottom,
		num_elements
	};
}

template<typename BitDepth>
class basic_cube_texture : public basic_texture_base<BitDepth> {
public:
	typedef basic_texture_base<BitDepth> base;
	typedef typename base::const_pointer const_pointer;
	typedef typename base::size_type size_type;

	virtual void set_data(cube_side::type side, const_pointer p, const lock_rect* r = 0) = 0;
	virtual size_type border_size() const = 0;
};

typedef basic_cube_texture<bit_depth32> cube_texture;
typedef shared_ptr<cube_texture> cube_texture_ptr;
typedef boost::array<cube_texture::const_pointer, cube_side::num_elements> cube_side_array;

template<typename BitDepth>
void set_cube_texture_data(basic_cube_texture<BitDepth>& t, const cube_side_array& src)
{
	for(unsigned i = 0; i < cube_side::num_elements; ++i)
		t.set_data(static_cast<cube_side::type>(i), src[i]);
}

}

#endif
