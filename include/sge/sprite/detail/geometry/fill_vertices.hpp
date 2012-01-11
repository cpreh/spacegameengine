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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_FILL_VERTICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_FILL_VERTICES_HPP_INCLUDED

#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/detail/visible.hpp>
#include <sge/sprite/detail/geometry/fill_color.hpp>
#include <sge/sprite/detail/geometry/fill_point_size.hpp>
#include <sge/sprite/detail/geometry/fill_position.hpp>
#include <sge/sprite/detail/geometry/fill_texture_levels.hpp>
#include <sge/sprite/detail/geometry/vertices_per_sprite.hpp>
#include <sge/sprite/detail/vf/format_part_from_object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
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
	typename It
>
sge::sprite::count const
fill_vertices(
	It _begin,
	It const _end,
	sge::renderer::vertex_buffer &_vb,
	sge::sprite::count const &_num_sprites
)
{
	typedef typename std::iterator_traits<
		It
	>::value_type object_type;

	typedef typename object_type::choices choices;

	sge::renderer::scoped_vertex_lock const vblock(
		_vb,
		sge::renderer::lock_mode::writeonly,
		sge::renderer::first_vertex(
			0
		),
		sge::renderer::vertex_count(
			_num_sprites.get()
			*
			sge::sprite::detail::geometry::vertices_per_sprite<
				choices
			>::value
		)
	);

	typedef sge::renderer::vf::view<
		typename sge::sprite::detail::vf::format_part_from_object<
			object_type
		>::type
	> vertex_view;

	vertex_view const vertices(
		vblock.value()
	);

	typename vertex_view::iterator vb_it(
		vertices.begin()
	);

	sge::sprite::count filled_sprites(
		0u
	);

	for(
		It it(
			_begin
		);
		it != _end;
		++it
	)
	{
		object_type const &spr(
			*it
		);

		if(
			!sge::sprite::detail::visible(
				spr
			)
		)
			continue;

		sge::sprite::detail::geometry::fill_position(
			vb_it,
			spr
		);

		sge::sprite::detail::geometry::fill_texture_levels(
			vb_it,
			spr
		);

		sge::sprite::detail::geometry::fill_color(
			vb_it,
			spr
		);

		sge::sprite::detail::geometry::fill_point_size(
			vb_it,
			spr
		);

		vb_it +=
			sge::sprite::detail::geometry::vertices_per_sprite<
				choices
			>::value;

		++filled_sprites;
	}

	return filled_sprites;
}

}
}
}
}

#endif
