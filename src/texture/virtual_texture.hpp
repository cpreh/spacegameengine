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
	virtual_texture(const lock_rect&, fragmented_texture&, bool repeatable = false);
	~virtual_texture();
	const lock_rect& area() const;
	const math::rect area_texc(space_unit repeat = 1) const;
	const tex_pos translate(const tex_pos &local_coords, space_unit repeat = 1) const;
	const tex_pos translate(tex_pos::value_type x, tex_pos::value_type y, space_unit repeat = 1) const;
	const texture_ptr my_texture() const;
	bool repeatable() const;
	void set_data(texture::const_pointer src);
private:
	const lock_rect& outer_area() const;
	lock_rect           outer_area_;
	fragmented_texture& fragment;
	bool                repeatable_;
	lock_rect           inner_area_;
};

typedef shared_ptr<virtual_texture>       virtual_texture_ptr;
typedef shared_ptr<const virtual_texture> const_virtual_texture_ptr;

}

#endif
