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

#include <iostream>
#include "../no_fragmented_texture.hpp"
#include "../../math.hpp"

sge::no_fragmented_texture::no_fragmented_texture(const renderer_ptr rend)
 : rend(rend)
{}

sge::virtual_texture_ptr sge::no_fragmented_texture::consume_fragments(const texture::size_type w, const texture::size_type h)
{
	if(tex)
		return virtual_texture_ptr();
	const texture::size_type next_w = next_pow_2(w),
	                         next_h = next_pow_2(h);

	tex = rend->create_texture(0, next_w, next_h, linear_filter); // TODO
	return virtual_texture_ptr(new virtual_texture(lock_rect(0,0,w,h), this, next_w == w && next_h == h));
}

void sge::no_fragmented_texture::return_fragments(const virtual_texture&)
{
	tex.reset();
}

sge::texture_ptr sge::no_fragmented_texture::get_texture() const
{
	return tex;
}

sge::fragmented_texture* sge::no_fragmented_texture::clone() const
{
	return new no_fragmented_texture(rend);
}
