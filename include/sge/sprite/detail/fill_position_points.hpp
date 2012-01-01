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


#ifndef SGE_SPRITE_DETAIL_FILL_POSITION_POINTS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_POSITION_POINTS_HPP_INCLUDED

#include <sge/sprite/detail/make_position.hpp>
#include <sge/sprite/detail/vector_float.hpp>
#include <sge/sprite/detail/vertex_pos.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Iterator,
	typename Choices
>
void
fill_position_points(
	Iterator const _iterator,
	object<
		Choices
	> const &_sprite
)
{
	typedef typename Choices::type_choices type_choices;

	typedef typename detail::vector_float<
		type_choices
	>::type vector_float;

	(*_iterator). template set<
		typename detail::vertex_pos<
			Choices
		>::type
	>(
		detail::make_position<
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

#endif
