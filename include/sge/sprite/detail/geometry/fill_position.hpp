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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_FILL_POSITION_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_FILL_POSITION_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_normal_size.hpp>
#include <sge/sprite/detail/config/has_point_size.hpp>
#include <sge/sprite/detail/config/has_rotation.hpp>
#include <sge/sprite/detail/geometry/fill_position_points.hpp>
#include <sge/sprite/detail/geometry/fill_position_rotated.hpp>
#include <sge/sprite/detail/geometry/fill_position_unrotated.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
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
typename boost::enable_if<
	boost::mpl::and_<
		sge::sprite::detail::config::has_rotation<
			Choices
		>,
		sge::sprite::detail::config::has_normal_size<
			Choices
		>
	>,
	void
>::type
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
		static_cast<
			typename sge::sprite::object<
				Choices
			>::rotation_type
		>(
			0.0001f
		)
	)
		sge::sprite::detail::geometry::fill_position_unrotated(
			_iterator,
			_sprite
		);
	else
		sge::sprite::detail::geometry::fill_position_rotated(
			_iterator,
			_sprite
		);
}

template<
	typename Iterator,
	typename Choices
>
typename boost::enable_if<
	boost::mpl::and_<
		boost::mpl::not_<
			sge::sprite::detail::config::has_rotation<
				Choices
			>
		>,
		sge::sprite::detail::config::has_normal_size<
			Choices
		>
	>,
	void
>::type
fill_position(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	sge::sprite::detail::geometry::fill_position_unrotated(
		_iterator,
		_sprite
	);
}

template<
	typename Iterator,
	typename Choices
>
typename boost::enable_if<
	sge::sprite::detail::config::has_point_size<
		Choices
	>
>::type
fill_position(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	sge::sprite::detail::geometry::fill_position_points(
		_iterator,
		_sprite
	);
}

}
}
}
}

#endif
