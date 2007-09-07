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


#include "../../exception.hpp"
#include "../static_texture.hpp"

sge::static_texture::static_texture(const texture_ptr tex)
: tex(tex),
  claimed(false)
{}

sge::virtual_texture_ptr sge::static_texture::consume_fragments(const texture::size_type w, const texture::size_type h)
{
	if(claimed)
		return virtual_texture_ptr();

	if(w > tex->width() || h > tex->height())
		throw exception("static_texture::consume_fragments(): size out of range.");
	claimed = true;
	return virtual_texture_ptr(new virtual_texture(lock_rect(0,0,w,h), this));
}

void sge::static_texture::return_fragments(const virtual_texture&)
{
	claimed = false;
}

sge::texture_ptr sge::static_texture::get_texture() const
{
	return tex;
}

sge::fragmented_texture* sge::static_texture::clone() const
{
	return 0; // FIXME
}
