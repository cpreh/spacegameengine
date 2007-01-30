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
#define M_PI 3.14159265
#endif

namespace sge
{

const double PI = M_PI;
//const double PI_2 = PI / 2;
//const double PI_3 = PI / 3;

//#define PI_2II6.28318530717958647692
//#define PI_OVER_2I1.57079632679489661923
//#define DTORII0.01745329251994329576
inline double deg_to_rad(const double deg)
{
	return deg * PI / 180;
}

inline double rad_to_deg(const double rad)
{
	return rad * 180 / PI;
}

}

#endif
