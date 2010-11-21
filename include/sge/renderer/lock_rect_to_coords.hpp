/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>

namespace sge
{
namespace renderer
{

template<
	typename Ret
>
typename fcppt::math::box::rect<
	Ret
>::type const
lock_rect_to_coords(
	lock_rect const &l,
	dim2 const &dim
)
{
	typedef typename fcppt::math::box::rect<
		Ret
	>::type ret_type;

	ret_type const srect(
		fcppt::math::box::structure_cast<
			ret_type
		>(
			l
		)
	);

	typedef typename fcppt::math::dim::static_<
		Ret,
		2
	>::type sdim_type;

	sdim_type const sdim(
		fcppt::math::dim::structure_cast<
			sdim_type
		>(
			dim
		)
	);

	return ret_type(
		typename ret_type::vector(
			srect.left() / sdim.w(),
			srect.top() / sdim.h()
		),
		srect.dimension() / sdim
	);
}

}
}

#endif
