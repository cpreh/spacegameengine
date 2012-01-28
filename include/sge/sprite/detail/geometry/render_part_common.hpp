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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_RENDER_PART_COMMON_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_RENDER_PART_COMMON_HPP_INCLUDED

#include <sge/renderer/first_vertex.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/buffers/vertex_count.hpp>
#include <sge/sprite/detail/roles/vertex_count.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename Choices,
	typename RenderPart
>
void
render_part_common(
	RenderPart &_render_part,
	sge::sprite::buffers::slice<
		Choices
	> const &_slice,
	sge::sprite::count const _offset,
	sge::sprite::count const _count
)
{
	_render_part. template set<
		sge::sprite::detail::roles::vertex_count
	>(
		sge::sprite::detail::buffers::vertex_count<
			Choices
		>(
			_count
		)
	);

	_render_part. template set<
		sge::sprite::buffers::roles::first_vertex
	>(
		sge::renderer::first_vertex(
			_slice.first_vertex().get()
			+
			sge::sprite::detail::buffers::vertex_count<
				Choices
			>(
				_offset
			).get()
		)
	);
}

}
}
}
}

#endif
