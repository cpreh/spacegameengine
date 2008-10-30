/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED
#define SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED

#include "dim_types.hpp"
#include "../math/rect.hpp"
#include "../math/rect_impl.hpp"
#include "../math/dim.hpp"

namespace sge
{
namespace renderer
{

template<
	typename T
>
math::basic_rect<T> const
lock_rect_to_coords(
	lock_rect const &l,
	dim_type const &dim,
	T const repeat)
{
	math::basic_rect<T> const srect(
		math::structure_cast<T>(l));
	
	math::basic_dim<T, 2> const sdim(
		math::structure_cast<T>(dim));

	return math::basic_rect<T>(
		srect.left() / sdim.w(),
		srect.top() / sdim.h(),
		repeat * srect.right() / sdim.w(),
		repeat * srect.bottom() / sdim.h());
}

}
}

#endif
