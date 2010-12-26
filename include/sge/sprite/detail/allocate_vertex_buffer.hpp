/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_ALLOCATE_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_ALLOCATE_VERTEX_BUFFER_HPP_INCLUDED

#include <sge/sprite/detail/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/roles/vertices_per_sprite.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename DynVertex,
	typename Buffers
>
void
allocate_vertex_buffer(
	sge::renderer:;device_ptr const _renderer,
	DynVertex const &_format,
	sge::renderer::size_type const _num_sprites,
	Buffers &_buffers
)
{
	_buffers. template set<
		detail::roles::vertex_buffer
	>(
		_renderer->create_vertex_buffer(
			_format,
			_num_sprites
			*
			detail::vertices_per_sprite<
				Choices
			>(),
			renderer::resource_flags::dynamic
		)
	);
}

}
}
}

#endif
