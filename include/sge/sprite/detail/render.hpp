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


#ifndef SGE_SPRITE_DETAIL_RENDER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_HPP_INCLUDED

#include <sge/sprite/detail/constants.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/texture/part.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename In,
	typename Comp
>
void render(
	In const beg,
	In const end,
	Comp const comp,
	renderer::device_ptr const rend,
	renderer::vertex_buffer_ptr const vb,
	renderer::index_buffer_ptr const ib)
{
	renderer::size_type offset(0);
	for(In cur(beg), next(cur); cur != end; cur = next )
	{
		renderer::size_type num_objects(0);

		while(next != end && comp(*cur, *next))
		{
			++next;
			++num_objects;
		}

		if(!cur->visible())
			continue;

		texture::const_part_ptr const vtex = cur->texture();

		rend->texture(
			vtex
			? vtex->texture()
			: renderer::const_texture_ptr(
				renderer::device::no_texture));
		
		rend->render(
			vb,
			ib,
			offset * detail::vertices_per_sprite,
			num_objects * detail::vertices_per_sprite,
			renderer::indexed_primitive_type::triangle,
			num_objects * 2,
			offset * detail::indices_per_sprite);

		offset += num_objects;
	}

	rend->texture(renderer::device::no_texture);
}

}
}
}

#endif
