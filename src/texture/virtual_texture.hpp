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


#ifndef SGE_VIRTUAL_TEXTURE_HPP_INCLUDED
#define SGE_VIRTUAL_TEXTURE_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include "../renderer/texture.hpp"
#include "../shared_ptr.hpp"

namespace sge
{

class fragmented_texture;

class virtual_texture : boost::noncopyable {
public:
	virtual_texture(const lock_rect&, fragmented_texture*, bool repeatable = false);
	~virtual_texture();
	lock_rect area() const;
	math::rect area_texc(space_unit repeat = 1) const;
	sge::tex_pos translate(const sge::tex_pos &local_coords, space_unit repeat = 1) const;
	inline sge::tex_pos translate(const sge::tex_pos::value_type x, const sge::tex_pos::value_type y, space_unit repeat = 1) const { return translate(sge::tex_pos(x, y), repeat); }
	texture_ptr my_texture() const;
	bool repeatable() const;
	void set_data(texture::const_pointer src);
private:
	lock_rect _area;
	fragmented_texture* fragment;
	bool _repeatable;
};

typedef shared_ptr<virtual_texture> virtual_texture_ptr;
typedef shared_ptr<const virtual_texture> const_virtual_texture_ptr;

}

#endif
