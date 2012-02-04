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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_RENDER_PART_INDEX_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_RENDER_PART_INDEX_HPP_INCLUDED

#include <sge/renderer/first_index.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/detail/buffers/index_count.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/detail/roles/primitive_count.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


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
typename boost::enable_if<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>,
	void
>::type
render_part_index(
	RenderPart &_render_part,
	sge::sprite::buffers::slice<
		Choices
	> const &_slice,
	sge::sprite::count const _offset,
	sge::sprite::count const _count
)
{
	_render_part. template set<
		sge::sprite::detail::roles::primitive_count
	>(
		sge::renderer::primitive_count(
			2u * _count.get()
		)
	);

	_render_part. template set<
		sge::sprite::buffers::roles::first_index
	>(
		sge::renderer::first_index(
			_slice.first_index().get()
			+
			sge::sprite::detail::buffers::index_count<
				Choices
			>(
				_offset
			).get()
		)
	);
}

template<
	typename Choices,
	typename RenderPart
>
typename boost::disable_if<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>,
	void
>::type
render_part_index(
	RenderPart &,
	sge::sprite::buffers::slice<
		Choices
	> const &,
	sge::sprite::count,
	sge::sprite::count
)
{
}

}
}
}
}

#endif
