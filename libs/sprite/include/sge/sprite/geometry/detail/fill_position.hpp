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
			0.0001f
		)
	)
		sge::sprite::geometry::detail::fill_position_unrotated(
			_iterator,
			_sprite
		);
	else
		sge::sprite::geometry::detail::fill_position_rotated(
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
	not
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
