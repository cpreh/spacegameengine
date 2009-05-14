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


#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/rect/intersects.hpp>
#include <algorithm>

template<
	typename T
>
sge::math::rect::basic<T> const
sge::math::rect::intersection(
	basic<T> const &r1,
	basic<T> const &r2)
{
	if (!intersects(r1,r2))
		return basic<T>::null();

	return rect<T>(
		std::max(r1.left(),r2.left()), 
		std::max(r1.top(),r2.top()), 
		std::min(r1.right(),r2.right()), 
		std::min(r1.bottom(),r2.bottom())
	);

}


