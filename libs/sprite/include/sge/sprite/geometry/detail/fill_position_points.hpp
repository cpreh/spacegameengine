//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_POINTS_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_POINTS_HPP_INCLUDED

#include <sge/sprite/detail/vf/pos.hpp>
#include <sge/sprite/geometry/detail/make_position.hpp>
#include <sge/sprite/types/basic/float_vector.hpp>


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
inline
void
fill_position_points(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	typedef
	sge::sprite::types::basic::float_vector<
		typename
		Choices::type_choices
	>
	vector_float;

	(*_iterator). template set<
		typename sge::sprite::detail::vf::pos<
			Choices
		>::type
	>(
		sge::sprite::geometry::detail::make_position<
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
