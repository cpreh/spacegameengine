/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_CONVERT_RECT_BASE_HPP_INCLUDED
#define SGE_D3D9_CONVERT_RECT_BASE_HPP_INCLUDED

#include "../d3dinclude.hpp"
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/has_dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{
namespace convert
{

template<
	typename Box
>
typename boost::enable_if<
	fcppt::math::box::has_dim<
		Box,
		2
	>,
	RECT
>::type const
rect_base(
	Box const &_rect
)
{
	RECT const ret =
	{
		static_cast<
			LONG
		>(
			_rect.left()
		),
		static_cast<
			LONG
		>(
			_rect.top()
		),
		static_cast<
			LONG
		>(
			_rect.right()
		),
		static_cast<
			LONG
		>(
			_rect.bottom()
		)
	};

	return ret;
}

}
}
}

#endif
