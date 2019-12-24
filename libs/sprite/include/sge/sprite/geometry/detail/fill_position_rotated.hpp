//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_ROTATED_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_ROTATED_HPP_INCLUDED

#include <sge/sprite/bounding_rect.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/geometry/detail/float_rect.hpp>
#include <sge/sprite/geometry/detail/make_position.hpp>
#include <sge/sprite/geometry/detail/vertices_per_sprite.hpp>
#include <sge/sprite/types/rotation.hpp>
#include <sge/sprite/types/basic/float.hpp>
#include <sge/sprite/types/basic/float_vector.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/matrix/row.hpp>
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
namespace geometry
{
namespace detail
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

	typedef sge::sprite::geometry::detail::float_rect<
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
		sge::sprite::geometry::detail::vertices_per_sprite<
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
		fcppt::math::matrix::row(
			cosx, -sinx
		),
		fcppt::math::matrix::row(
			sinx,  cosx
		)
	);

	typedef
	sge::sprite::detail::vf::pos<
		Choices
	>
	vertex_pos;

	for(
		auto const &cur_pos
		:
		positions
	)
		(*_iterator++). template set<
			vertex_pos
		>(
			sge::sprite::geometry::detail::make_position<
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
