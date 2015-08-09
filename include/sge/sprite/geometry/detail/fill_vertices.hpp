/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_VERTICES_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_VERTICES_HPP_INCLUDED

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/buffers/vertex_count.hpp>
#include <sge/sprite/geometry/detail/fill_color.hpp>
#include <sge/sprite/geometry/detail/fill_point_size.hpp>
#include <sge/sprite/geometry/detail/fill_position.hpp>
#include <sge/sprite/geometry/detail/fill_texture_levels.hpp>
#include <sge/sprite/geometry/detail/make_render_part.hpp>
#include <sge/sprite/geometry/detail/vertices_per_sprite.hpp>
#include <sge/sprite/detail/vf/format_part_from_object.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Range,
	typename Compare,
	typename Choices
>
sge::sprite::render::range<
	Choices
>
fill_vertices(
	Range const &_range,
	Compare const &_compare,
	sge::sprite::buffers::slice<
		Choices
	> const &_slice
)
{
	typedef
	sge::sprite::render::range<
		Choices
	>
	result_type;

	typedef
	typename
	Range::iterator
	iterator;

	iterator const
		begin(
			_range.begin()
		),
		end(
			_range.end()
		);

	typedef
	typename
	std::iterator_traits<
		iterator
	>::value_type
	object_type;

	typedef
	typename
	object_type::choices
	choices;

	sge::renderer::vertex::scoped_lock const vblock(
		_slice.vertex_buffer(),
		sge::renderer::lock_mode::writeonly,
		_slice.first_vertex(),
		sge::sprite::buffers::vertex_count<
			Choices
		>(
			_range.size()
		)
	);

	typedef sge::renderer::vf::view<
		sge::sprite::detail::vf::format_part_from_object<
			object_type
		>
	> vertex_view;

	vertex_view const vertices(
		vblock.value()
	);

	typename vertex_view::iterator vb_it(
		vertices.begin()
	);

	typedef
	typename
	result_type::range_part_vector
	range_part_vector;

	range_part_vector result;

	sge::sprite::count offset(
		0u
	);

	sge::sprite::count cur_count(
		0u
	);

	// TODO: Simplify this!
	for(
		iterator cur(
			begin
		);
		cur != end;
		++cur
	)
	{
		iterator const next(
			std::next(
				cur
			)
		);

		++cur_count;

		object_type const &cur_sprite(
			*cur
		);

		if(
			next
			==
			end
			||
			_compare(
				cur_sprite,
				*next
			)
			||
			_compare(
				*next,
				cur_sprite
			)
		)
		{
			result.push_back(
				sge::sprite::geometry::detail::make_render_part(
					_slice,
					offset,
					cur_count,
					cur_sprite
				)
			);

			offset += cur_count;

			cur_count =
				sge::sprite::count(
					0u
				);
		}

		sge::sprite::geometry::detail::fill_position(
			vb_it,
			cur_sprite
		);

		sge::sprite::geometry::detail::fill_texture_levels(
			vb_it,
			cur_sprite
		);

		sge::sprite::geometry::detail::fill_color(
			vb_it,
			cur_sprite
		);

		sge::sprite::geometry::detail::fill_point_size(
			vb_it,
			cur_sprite
		);

		vb_it +=
			sge::sprite::geometry::detail::vertices_per_sprite<
				choices
			>::value;
	}

	return
		result_type(
			_slice.buffer_object(),
			std::move(
				result
			)
		);
}

}
}
}
}

#endif
