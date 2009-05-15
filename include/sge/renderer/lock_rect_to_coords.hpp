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



#ifndef SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED
#define SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED

#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/rect/structure_cast.hpp>
#include <sge/math/dim/static.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/structure_cast.hpp>

namespace sge
{
namespace renderer
{

template<
	typename T
>
math::rect::basic<T> const
lock_rect_to_coords(
	lock_rect const &l,
	dim_type const &dim,
	T const repeat)
{
	typedef math::rect::basic<T> ret_type;

	ret_type const srect(
		math::rect::structure_cast<ret_type>(l)
	);
	
	typedef typename math::dim::static_<T, 2>::type sdim_type;

	sdim_type const sdim(
		math::dim::structure_cast<sdim_type>(dim)
	);

	return math::rect::basic<T>(
		srect.left() / sdim.w(),
		srect.top() / sdim.h(),
		repeat * srect.right() / sdim.w(),
		repeat * srect.bottom() / sdim.h()
	);
}

}
}

#endif
