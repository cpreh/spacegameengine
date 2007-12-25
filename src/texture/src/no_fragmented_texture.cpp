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


#include <iostream>
#include <ostream>
#include "../no_fragmented_texture.hpp"
#include "../atlasing.hpp"
#include "../../math/utility.hpp"

sge::no_fragmented_texture::no_fragmented_texture(const renderer_ptr rend, const filter_args& my_filter)
 : rend(rend),
   my_filter(my_filter)
{}

const sge::virtual_texture_ptr sge::no_fragmented_texture::consume_fragments(const texture::dim_type& dim)
{
	if(tex)
		return virtual_texture_ptr();

	const texture::dim_type next_dim(math::next_pow_2(dim));

   	tex = rend->create_texture(0, next_dim, my_filter);

	const bool no_atlasing = next_dim == dim;

	static bool warn_once = false;
	if(!no_atlasing && !warn_once)
	{
		warn_once = true;
		std::cerr << "warning: You used a no_fragmented_texture whose dimensions are not a power of 2."\
		             " This is slower to load and requires more texture memory because it needs atlasing and thus is not intuitive."\
			     " The texture's size was " << dim << "."\
			     " This message will only be displayed once.\n";
	}

	return virtual_texture_ptr(new virtual_texture(lock_rect(lock_rect::point_type(0,0), no_atlasing ? dim : atlased_size(dim)), *this, no_atlasing));
}

void sge::no_fragmented_texture::return_fragments(const virtual_texture&)
{
	tex.reset();
}

const sge::texture_ptr sge::no_fragmented_texture::get_texture() const
{
	return tex;
}

bool sge::no_fragmented_texture::repeatable() const
{
	return true;
}
