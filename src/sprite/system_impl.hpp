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


#ifndef SGE_SPRITE_SYSTEM_IMPL_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_IMPL_HPP_INCLUDED

#include <algorithm>
#include <iterator>
#include "helper.hpp"
#include "sprite.hpp"
#include "system.hpp"
#include "../algorithm.hpp"
#include "../renderer/lock_ptr.hpp"

template<typename RanIt>
void sge::sprite_system::render(const RanIt beg, const RanIt end)
{
	std::sort(beg, end, &sprite::less);
	
	const typename std::iterator_traits<RanIt>::difference_type range_len = std::distance(beg,end);

	if(vb->size() < static_cast<vertex_buffer::size_type>(range_len) * detail::vertices_per_sprite)
	{
		vb->resize(range_len * detail::vertices_per_sprite);
		ib->resize(range_len * detail::indices_per_sprite);
	}

	{
		lock_ptr<index_buffer_ptr> iblock(ib);
		lock_ptr<vertex_buffer_ptr> vblock(vb);
		index_buffer::iterator ib_it = ib->begin();
		vertex_buffer::iterator vb_it = vb->begin();

		for(RanIt cur = beg; cur != end; ++cur)
		{
			sprite& spr = *cur;
			
			ib_it = fill_sprite_indices(ib_it, static_cast<index_buffer::value_type>(vb_it - vb->begin()));

			if(spr.rotation() == 0)
				fill_sprite_position(vb_it, spr.get_rect(), spr.z());
			else
				fill_sprite_position_rotated(vb_it, spr.get_rect(), spr.rotation(), spr.rotation_center(), spr.z());

			for(stage_type i = 0; i < max_tex_level() && spr.get_texture(i); ++i)
				fill_sprite_tex_coordinates(vb_it, spr.get_texture(i)->area_texc(spr.repeat()), i);

			vb_it = fill_sprite_color(vb_it, spr.get_color());
		}
	}

	set_parameters();
	unsigned first_index = 0;
	for(RanIt cur = beg; cur != end; )
	{
		if(!cur->visible())
			break;

		unsigned num_objects;
		const RanIt next = first_mismatch_if(cur, end, num_objects, &sprite::equal);

		for(stage_type stage = 0; stage < max_tex_level(); ++stage)
		{
			const virtual_texture_ptr vtex = cur->get_texture(stage);
			rend->set_texture(vtex ? vtex->my_texture() : texture_ptr(), stage);
		}
		rend->render(vb, ib, (cur - beg) * detail::vertices_per_sprite, (next - beg) * detail::vertices_per_sprite, indexed_primitive_type::triangle, num_objects*2, first_index);
		first_index += num_objects * detail::indices_per_sprite;
		cur = next;
	}

	for(stage_type stage = 1; stage < max_tex_level(); ++stage)
		rend->set_texture(texture_ptr(), stage);
}

#endif
