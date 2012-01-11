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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_FILL_POSITION_POINTS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_FILL_POSITION_POINTS_HPP_INCLUDED

#include <sge/sprite/detail/geometry/make_position.hpp>
#include <sge/sprite/detail/geometry/vector_float.hpp>
#include <sge/sprite/detail/vf/pos.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename Iterator,
	typename Choices
>
void
fill_position_points(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	typedef typename sge::sprite::detail::geometry::vector_float<
		Choices
	>::type vector_float;

	(*_iterator). template set<
		typename sge::sprite::detail::vf::pos<
			Choices
		>::type
	>(
		sge::sprite::detail::geometry::make_position<
			Choices
		>(
			vector_float(
				static_cast<
					typename vector_float::value_type
				>(
					_sprite.x()
				),
				static_cast<
					typename vector_float::value_type
				>(
					_sprite.y()
				)
			),
			_sprite
		)
	);

}

}
}
}
}

#endif
