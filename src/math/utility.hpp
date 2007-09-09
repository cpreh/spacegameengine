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
#ifndef SGE_UTILITY_HPP_INCLUDED
#define SGE_UTILITY_HPP_INCLUDED

#include <cstdlib>

namespace sge
{
namespace math
{

template<typename T>
bool almost_zero(const T t)
{
	return t > T(-0.001) && t < T(0.001);
}

template<typename T>
T abs(const T &t) 
{ 
	return t >= T(0) ? t : -t; 
}

inline unsigned unsigned_diff(const unsigned a,const unsigned b)
{
	return a > b ? a - b : b - a;
}

template<typename T>
T random(const T &begin,const T &end)
{
	return begin + T(std::rand() / (RAND_MAX + 1.0) * (end - begin));
}

}
}

#endif
