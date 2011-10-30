/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_ALLOCATE_INDEX_BUFFER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_ALLOCATE_INDEX_BUFFER_HPP_INCLUDED

#include <sge/renderer/device.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/sprite/detail/indices_per_sprite.hpp>
#include <sge/sprite/detail/roles/index_buffer.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Elements,
	typename Buffers
>
void
allocate_index_buffer(
	sge::renderer::device &_renderer,
	sge::renderer::size_type const _num_sprites,
	Buffers &_buffers
)
{
	_buffers. template set<
		detail::roles::index_buffer
	>(
		_renderer.create_index_buffer(
			renderer::index::dynamic::format::i16,
			renderer::index_count(
				_num_sprites
				*
				detail::indices_per_sprite<
					Elements
				>()
			),
			renderer::resource_flags::dynamic
		)
	);
}

}
}
}

#endif
