/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_ROTATION_CENTER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_ROTATION_CENTER_HPP_INCLUDED

#include <sge/sprite/roles/rotate_around.hpp>
#include <sge/sprite/roles/use_rotation.hpp>
#include <sge/sprite/center.hpp>
#include <sge/sprite/with_rotation_center.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
typename boost::enable_if<
	boost::mpl::contains<
		typename Choices::elements,
		with_rotation_center
	>,
	typename object<
		Choices
	>::point
>::type
rotation_center(
	object<
		Choices
	> const &sprite_
)
{
	return
		sprite_. template get<
			sge::sprite::roles::use_rotation
		>()
		?
			sprite_. template get<
				sge::sprite::roles::rotate_around
			>()
		:
			center(
				sprite_
			);
}

template<
	typename Choices
>
typename boost::disable_if<
	boost::mpl::contains<
		typename Choices::elements,
		with_rotation_center
	>,
	typename object<
		Choices
	>::point
>::type
rotation_center(
	object<
		Choices
	> const &sprite_
)
{
	return
		center(
			sprite_
		);
}

}
}
}

#endif
