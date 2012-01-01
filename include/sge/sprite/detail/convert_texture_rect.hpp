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


#ifndef SGE_SPRITE_DETAIL_CONVERT_TEXTURE_RECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONVERT_TEXTURE_RECT_HPP_INCLUDED

#include <sge/sprite/texture_coordinates.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Rect
>
typename texture_coordinates<
	typename Rect::value_type
>::type const
convert_texture_rect(
	Rect const &_rect
)
{
	typedef typename texture_coordinates<
		typename Rect::value_type
	>::type return_type;

	typedef typename return_type::first_type element_type;

	return
		return_type(
			element_type(
				_rect.left(),
				_rect.top()
			),
			element_type(
				_rect.right(),
				_rect.bottom()
			)
		);
}

}
}
}

#endif
