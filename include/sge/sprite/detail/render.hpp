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


#ifndef SGE_SPRITE_RENDER_HPP_INCLUDED
#define SGE_SPRITE_RENDER_HPP_INCLUDED

#include "../../renderer/size_type.hpp"
#include "../../renderer/device.hpp"
#include "../../renderer/texture.hpp"
#include "../../texture/part.hpp"
#include "../../algorithm/first_mismatch.hpp"
#include <iterator>

namespace sge
{
namespace sprite
{

template<typename In, typename Comp>
void render(
	In const beg,
	In const end,
	Comp const comp,
	renderer::device_ptr const rend,
	renderer::vertex_buffer_ptr const vb,
	renderer::index_buffer_ptr const ib)
{
	renderer::size_type first_index = 0;
	for(In cur(beg); cur != end; )
	{
		renderer::size_type num_objects;
		In const next = first_mismatch_if(
			cur,
			end,
			num_objects,
			comp);

		texture::part_ptr const vtex = cur->texture();
		rend->set_texture(
			vtex
			? vtex->texture()
			: renderer::device::no_texture);
		
		rend->render(
			vb,
			ib,
			std::distance(beg, cur) * detail::vertices_per_sprite,
			std::distance(cur, next) * detail::vertices_per_sprite,
			renderer::indexed_primitive_type::triangle,
			num_objects * 2,
			first_index);
		first_index += num_objects * detail::indices_per_sprite;
		cur = next;
	}

	rend->set_texture(renderer::device::no_texture);
}

}
}

#endif
