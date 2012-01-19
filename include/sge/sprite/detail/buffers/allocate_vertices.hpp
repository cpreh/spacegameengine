/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_VERTICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_VERTICES_HPP_INCLUDED

#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/detail/geometry/vertices_per_sprite.hpp>
#include <sge/sprite/detail/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/vf/part_index.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace buffers
{

template<
	typename Choices,
	typename Buffers
>
void
allocate_vertices(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vertex_declaration,
	sge::sprite::count const _num_sprites,
	Buffers &_buffers,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	_buffers. template set<
		sge::sprite::detail::roles::vertex_buffer
	>(
		_renderer.create_vertex_buffer(
			_vertex_declaration,
			sge::sprite::detail::vf::part_index(),
			sge::renderer::vertex_count(
				_num_sprites.get()
				*
				sge::sprite::detail::geometry::vertices_per_sprite<
					Choices
				>::value
			),
			_resource_flags
		)
	);
}

}
}
}
}

#endif
