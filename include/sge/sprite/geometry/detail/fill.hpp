/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_HPP_INCLUDED

#include <sge/sprite/buffers/slice_fwd.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/geometry/detail/fill_indices.hpp>
#include <sge/sprite/geometry/detail/fill_vertices.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
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
inline
typename
boost::enable_if<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>,
	sge::sprite::render::range<
		Choices
	>
>::type
fill(
	Range const &_range,
	Compare const &_compare,
	sge::sprite::buffers::slice<
		Choices
	> const &_slice
)
{
	sge::sprite::geometry::detail::fill_indices<
		Choices
	>(
		_range.size(),
		_slice
	);

	return
		sge::sprite::geometry::detail::fill_vertices(
			_range,
			_compare,
			_slice
		);
}

template<
	typename Range,
	typename Compare,
	typename Choices
>
inline
typename
boost::disable_if<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>,
	sge::sprite::render::range<
		Choices
	>
>::type
fill(
	Range const &_range,
	Compare const &_compare,
	sge::sprite::buffers::slice<
		Choices
	> &_slice
)
{
	return
		sge::sprite::geometry::detail::fill_vertices(
			_range,
			_compare,
			_slice
		);
}

}
}
}
}

#endif
