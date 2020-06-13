//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_normal_size.hpp>
#include <sge/sprite/detail/config/has_point_size.hpp>
#include <sge/sprite/detail/config/has_rotation.hpp>
#include <sge/sprite/geometry/detail/fill_position_points.hpp>
#include <sge/sprite/geometry/detail/fill_position_rotated.hpp>
#include <sge/sprite/geometry/detail/fill_position_unrotated.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <type_traits>
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
inline
std::enable_if_t<
	sge::sprite::detail::config::has_rotation<
		Choices
	>::value
	&&
	sge::sprite::detail::config::has_normal_size<
		Choices
	>::value,
	void
>
fill_position(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	if(
		std::abs(
			_sprite.rotation()
		)
		<
		fcppt::literal<
			typename
			sge::sprite::object<
				Choices
			>::rotation_type
		>(
			0.0001F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		)
	)
	{
		sge::sprite::geometry::detail::fill_position_unrotated(
			_iterator,
			_sprite
		);
	}
	else
	{
		sge::sprite::geometry::detail::fill_position_rotated(
			_iterator,
			_sprite
		);
	}
}

template<
	typename Iterator,
	typename Choices
>
inline
std::enable_if_t<
	fcppt::not_(
		sge::sprite::detail::config::has_rotation<
			Choices
		>::value
	)
	&&
	sge::sprite::detail::config::has_normal_size<
		Choices
	>::value,
	void
>
fill_position(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	sge::sprite::geometry::detail::fill_position_unrotated(
		_iterator,
		_sprite
	);
}

template<
	typename Iterator,
	typename Choices
>
inline
std::enable_if_t<
	sge::sprite::detail::config::has_point_size<
		Choices
	>::value
>
fill_position(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	sge::sprite::geometry::detail::fill_position_points(
		_iterator,
		_sprite
	);
}

}
}
}
}

#endif
