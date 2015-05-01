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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_FILL_POSITION_ROTATED_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_FILL_POSITION_ROTATED_HPP_INCLUDED

#include <sge/sprite/bounding_rect.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/geometry/float_rect.hpp>
#include <sge/sprite/detail/geometry/make_position.hpp>
#include <sge/sprite/detail/geometry/vertices_per_sprite.hpp>
#include <sge/sprite/types/rotation.hpp>
#include <sge/sprite/types/basic/float.hpp>
#include <sge/sprite/types/basic/float_vector.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cmath>
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
	typename Iterator,
	typename Choices
>
void
fill_position_rotated(
	Iterator _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	typedef typename Choices::type_choices type_choices;

	typedef sge::sprite::types::basic::float_<
		type_choices
	> funit;

	typedef sge::sprite::types::basic::float_vector<
		type_choices
	> pos2;

	pos2 const centerf(
		fcppt::math::vector::structure_cast<
			pos2,
			fcppt::cast::static_cast_fun
		>(
			_sprite.center()
		)
	);

	typedef sge::sprite::detail::geometry::float_rect<
		type_choices
	> float_rect;

	float_rect const rbs(
		fcppt::math::box::structure_cast<
			float_rect,
			fcppt::cast::static_cast_fun
		>(
			sge::sprite::bounding_rect(
				_sprite
			)
		)
	);

	typedef std::array<
		pos2,
		sge::sprite::detail::geometry::vertices_per_sprite<
			Choices
		>::value
	> position_array;

	position_array const positions{{
		pos2(
			rbs.left(),
			rbs.top()
		) - centerf,
		pos2(
			rbs.right(),
			rbs.top()
		) - centerf,
		pos2(
			rbs.right(),
			rbs.bottom()
		) - centerf,
		pos2(
			rbs.left(),
			rbs.bottom()
		) - centerf
	}};

	typedef sge::sprite::types::rotation<
		type_choices
	> rotation_type;

	rotation_type const rot(
		_sprite.rotation()
	);

	funit const
		sinx(
			std::sin(
				rot
			)
		),
		cosx(
			std::cos(
				rot
			)
		);

	typedef fcppt::math::matrix::static_<
		funit,
		2,
		2
	> matrix2x2;

	matrix2x2 const mat_rot(
		cosx, -sinx,
		sinx,  cosx
	);

	typedef typename sge::sprite::detail::vf::pos<
		Choices
	>::type vertex_pos;

	for(
		auto const &cur_pos
		:
		positions
	)
		(*_iterator++). template set<
			vertex_pos
		>(
			sge::sprite::detail::geometry::make_position<
				Choices
			>(
				(mat_rot * cur_pos) + centerf,
				_sprite
			)
		);
}

}
}
}
}

#endif
