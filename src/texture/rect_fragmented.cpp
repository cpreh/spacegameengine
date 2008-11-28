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


#include <sge/texture/rect_fragmented.hpp>
#include <sge/texture/atlasing.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/device.hpp>

sge::texture::rect_fragmented::rect_fragmented(
	renderer::device_ptr const rend,
	renderer::color_format::type const format,
	renderer::texture_filter const &filter)
:
	rend(rend),
	cur_x(0),
	cur_y(0),
	cur_height(0),
	tex(
		atlased_texture(
			rend,
			format,
			filter))
{}

sge::texture::part_ptr const
sge::texture::rect_fragmented::consume_fragment(
	renderer::dim_type const &dim)
{
	renderer::texture::dim_type const atlased_dim(
		atlased_size(
			dim,
			true));

	// if there is no space left for the requested height
	if(cur_y + dim.h() >= tex->dim().h())
		return part_ptr();

	// if the current line is full advance to the next
	if(cur_x + dim.w() >= tex->dim().w())
	{
		cur_x = 0;
		cur_y += cur_height;
		cur_height = 0;
	}

	if(cur_y + dim.h() >= tex->dim().h())
		return part_ptr();

	part_ptr const ret(
		new part_fragmented(
			renderer::lock_rect(
				renderer::lock_rect::point_type(
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

void sge::texture::rect_fragmented::return_fragment(
	part const &)
{
	// FIXME
}

sge::renderer::texture_ptr const
sge::texture::rect_fragmented::texture() const
{
	return tex;
}

bool sge::texture::rect_fragmented::repeatable() const
{
	return false;
}
