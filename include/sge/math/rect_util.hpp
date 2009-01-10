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


#ifndef SGE_MATH_RECT_UTIL_HPP_INCLUDED
#define SGE_MATH_RECT_UTIL_HPP_INCLUDED

#include "rect.hpp"

namespace sge
{
namespace math
{

template<typename T>
bool contains(const rect<T>& r, const vector<T,2>& p);

template<typename T>
rect<T> const intersection(rect<T> const &,rect<T> const &);

template<typename T,typename U>
rect<T> const bounding(U begin,U const end);

template<typename T>
bool contains(const rect<T>& outer, const rect<T>& inner);

template<typename T>
bool intersects(const rect<T>& l, const rect<T>& r);

}
}

#include "detail/rect_util_impl.hpp"

#endif
