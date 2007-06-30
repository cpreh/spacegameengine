/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_MATH_CONSTANTS_HPP_INCLUDED
#define SGE_MATH_CONSTANTS_HPP_INCLUDED

#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058
#endif

namespace sge
{
namespace math
{

const double PI = M_PI;
const long double PI_L =
	3.1415926535897932384626433832795028841971693993751058L;
const double DEGREE =
	0.0174532925199432957692369076848861271344287188854172;
const long double DEGREE_L =
	0.0174532925199432957692369076848861271344287188854172L;

template<typename T>
inline T deg_to_rad(const T deg)
{
	return deg * PI / static_cast<T>(180);
}

template<typename T>
inline T rad_to_deg(const T rad)
{
	return rad * static_cast<T>(180) / PI;
}

}

}

#endif
