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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_UNROTATED_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_UNROTATED_HPP_INCLUDED

#include <sge/sprite/bounding_rect.hpp>
#include <sge/sprite/detail/vf/pos.hpp>
#include <sge/sprite/geometry/detail/float_rect.hpp>
#include <sge/sprite/geometry/detail/make_position.hpp>
#include <sge/sprite/types/basic/float_vector.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/math/box/structure_cast.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Iterator,
	typename Choices
>
void
fill_position_unrotated(
	Iterator _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	typedef typename Choices::type_choices type_choices;

	typedef typename sge::sprite::detail::vf::pos<
		Choices
	>::type vertex_pos;

	typedef sge::sprite::geometry::detail::float_rect<
		type_choices
	> float_rect;

	float_rect const rect(
		fcppt::math::box::structure_cast<
			float_rect,
			fcppt::cast::static_cast_fun
		>(
			sge::sprite::bounding_rect(
				_sprite
			)
		)
	);

	typedef sge::sprite::types::basic::float_vector<
		type_choices
	> float_vector;

	(*_iterator++). template set<
		vertex_pos
	>(
		sge::sprite::geometry::detail::make_position<
			Choices
		>(
			float_vector(
				rect.left(),
				rect.top()
			),
			_sprite
		)
	);

	(*_iterator++). template set<
		vertex_pos
	>(
		sge::sprite::geometry::detail::make_position<
			Choices
		>(
			float_vector(
				rect.right(),
				rect.top()
			),
			_sprite
		)
	);

	(*_iterator++). template set<
		vertex_pos
	>(
		sge::sprite::geometry::detail::make_position<
			Choices
		>(
			float_vector(
				rect.right(),
				rect.bottom()
			),
			_sprite
		)
	);

	(*_iterator++). template set<
		vertex_pos
	>(
		sge::sprite::geometry::detail::make_position<
			Choices
		>(
			float_vector(
				rect.left(),
				rect.bottom()
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
