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


#include "../rect_fragmented_texture.hpp"
#include "../atlasing.hpp"

sge::rect_fragmented_texture::rect_fragmented_texture(const renderer_ptr rend, const filter_args& my_filter)
: rend(rend),
  my_filter(my_filter),
  cur_x(0),
  cur_y(0),
  cur_height(0),
  tex(atlased_texture(rend, my_filter))
{}

const sge::virtual_texture_ptr sge::rect_fragmented_texture::consume_fragments(const texture::dim_type& dim)
{
	const texture::dim_type atlased_dim(atlased_size(dim));

	// if there is no space left for the requested height
	if(cur_y + dim.h() >= tex->dim().h())
		return virtual_texture_ptr();

	// if the current line is full advance to the next
	if(cur_x + dim.w() >= tex->dim().w())
	{
		cur_x = 0;
		cur_y += cur_height;
		cur_height = 0;
	}

	if(cur_y + dim.h() >= tex->dim().h())
		return virtual_texture_ptr();

	const virtual_texture_ptr ret(
		new virtual_texture(
			lock_rect(
				lock_rect::point_type(
					cur_x,
					cur_y),
				atlased_dim),
				*this,
				true,
				true));

	cur_x += dim.w() + 1;
	cur_height = std::max(cur_height, dim.h());

	return ret;
}

void sge::rect_fragmented_texture::return_fragments(const virtual_texture&)
{
	// FIXME
}

const sge::texture_ptr sge::rect_fragmented_texture::get_texture() const
{
	return tex;
}

bool sge::rect_fragmented_texture::repeatable() const
{
	return false;
}
