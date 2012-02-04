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

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/detail/buffers/vertex_count.hpp>
#include <sge/sprite/detail/geometry/fill_color.hpp>
#include <sge/sprite/detail/geometry/fill_point_size.hpp>
#include <sge/sprite/detail/geometry/fill_position.hpp>
#include <sge/sprite/detail/geometry/fill_texture_levels.hpp>
#include <sge/sprite/detail/geometry/make_render_part.hpp>
#include <sge/sprite/detail/geometry/vertices_per_sprite.hpp>
#include <sge/sprite/detail/vf/format_part_from_object.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <exception>
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
	typename Range,
	typename Compare,
	typename Choices
>
sge::sprite::render::range<
	Choices
> const
fill_vertices(
	Range const &_range,
	Compare const &_compare,
	sge::sprite::buffers::slice<
		Choices
	> &_slice
)
{
	if(
		_range.empty()
	)
		std::terminate();

	typedef typename Range::iterator iterator;

	iterator const
		begin(
			_range.begin()
		),
		end(
			_range.end()
		);

	typedef typename std::iterator_traits<
		iterator
	>::value_type object_type;

	typedef typename object_type::choices choices;

	sge::renderer::scoped_vertex_lock const vblock(
		_slice.vertex_buffer(),
		sge::renderer::lock_mode::writeonly,
		_slice.first_vertex(),
		sge::sprite::detail::buffers::vertex_count<
			Choices
		>(
			_range.size()
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

	typedef sge::sprite::render::range<
		Choices
	> result_type;

	result_type result(
		_slice.part_vector(),
		_slice.buffer_object()
	);

	sge::sprite::count offset(
		0u
	);

	sge::sprite::count cur_count(
		0u
	);

	for(
		iterator cur(
			begin
		);
		cur != end;
		++cur
	)
	{
		iterator const next(
			boost::next(
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
			result.add(
				sge::sprite::detail::geometry::make_render_part(
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

		sge::sprite::detail::geometry::fill_position(
			vb_it,
			cur_sprite
		);

		sge::sprite::detail::geometry::fill_texture_levels(
			vb_it,
			cur_sprite
		);

		sge::sprite::detail::geometry::fill_color(
			vb_it,
			cur_sprite
		);

		sge::sprite::detail::geometry::fill_point_size(
			vb_it,
			cur_sprite
		);

		vb_it +=
			sge::sprite::detail::geometry::vertices_per_sprite<
				choices
			>::value;
	}

	return result;
}

}
}
}
}

#endif
