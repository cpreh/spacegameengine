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

#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_shared_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/vertex_count.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/vf/part_index.hpp>


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
	typename BufferObject
>
void
allocate_vertices(
	sge::sprite::buffers::parameters const &_parameters,
	sge::sprite::count const _num_sprites,
	BufferObject &_buffers,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	_buffers. template set<
		sge::sprite::buffers::roles::vertex_buffer
	>(
		sge::renderer::vertex::buffer_shared_ptr(
			_parameters.device().create_vertex_buffer(
				sge::renderer::vertex::buffer_parameters(
					_parameters.vertex_declaration(),
					sge::sprite::detail::vf::part_index(),
					sge::sprite::buffers::vertex_count<
						Choices
					>(
						_num_sprites
					),
					_resource_flags
				)
			)
		)
	);
}

}
}
}
}

#endif
