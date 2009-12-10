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


#ifndef SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_RECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_RECT_HPP_INCLUDED

#include <sge/sprite/detail/point_float.hpp>
#include <sge/sprite/detail/rect_float.hpp>
#include <sge/sprite/detail/vertex_texpos.hpp>
#include <sge/math/box/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename Iterator
>
void
fill_tex_coordinates_rect(
	Iterator iterator,
	typename rect_float<
		typename Choices::type_choices
	>::type const &rt
)
{
	typedef typename Choices::type_choices type_choices;

	typedef typename point_float<
		type_choices
	>::type tex_pos;

	typedef typename detail::vertex_texpos<
		type_choices
	>::type vertex_texpos;

	(*iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			rt.left(),
			rt.top()
		)
	);

	(*iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			rt.right(),
			rt.top()
		)
	);

	(*iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			rt.right(),
			rt.bottom()
		)
	);

	(*iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			rt.left(),
			rt.bottom()
		)
	);
}

}
}
}

#endif
