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


#include "../atlasing.hpp"
#include "../../math/rect_impl.hpp"

sge::texture::size_type sge::atlased_gap()
{
	return 1;
}

sge::texture::size_type sge::atlased_size(const texture::size_type s)
{
	return s + 2 * atlased_gap();
}

const sge::texture::dim_type sge::atlased_size(const texture::dim_type& dim)
{
	return texture::dim_type(atlased_size(dim.w()), atlased_size(dim.h()));
}

const sge::texture::dim_type sge::atlased_texture_dim(const renderer_ptr rend)
{
	const texture::size_type max_size = rend->caps().max_tex_size;
	return texture::dim_type(max_size, max_size);
}

const sge::texture_ptr sge::atlased_texture(const renderer_ptr rend, const filter_args& filter)
{
	return rend->create_texture(0, atlased_texture_dim(rend), filter);
}

const sge::lock_rect sge::inner_atlased_rect(const lock_rect& outer)
{
	return resize_borders(outer, atlased_gap());
}
