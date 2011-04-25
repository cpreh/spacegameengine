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


#ifndef SGE_PROJECTILE_TRIANGULATION_DETAIL_POINT_INSIDE_TRIANGLE_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_DETAIL_POINT_INSIDE_TRIANGLE_HPP_INCLUDED

namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace detail
{
// Should work on a variety of types, requirements:
// - Point has a ::value_type
// - Point::value_type is a ring
template<typename Point>
bool 
point_inside_triangle(
	Point const &a,
	Point const &b,
	Point const &c,
	Point const &p)
{
	typedef typename
	Point::value_type
	scalar;

  scalar ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
  scalar cCROSSap, bCROSScp, aCROSSbp;

  ax = static_cast<scalar>(c[0] - b[0]);  ay = static_cast<scalar>(c[1] - b[1]);
  bx = static_cast<scalar>(a[0] - c[0]);  by = static_cast<scalar>(a[1] - c[1]);
  cx = static_cast<scalar>(b[0] - a[0]);  cy = static_cast<scalar>(b[1] - a[1]);
  apx= static_cast<scalar>(p[0] - a[0]);  apy= static_cast<scalar>(p[1] - a[1]);
  bpx= static_cast<scalar>(p[0] - b[0]);  bpy= static_cast<scalar>(p[1] - b[1]);
  cpx= static_cast<scalar>(p[0] - c[0]);  cpy= static_cast<scalar>(p[1] - c[1]);

  aCROSSbp = static_cast<scalar>(ax*bpy - ay*bpx);
  cCROSSap = static_cast<scalar>(cx*apy - cy*apx);
  bCROSScp = static_cast<scalar>(bx*cpy - by*cpx);

  return 
		aCROSSbp >= static_cast<scalar>(0) && 
		bCROSScp >= static_cast<scalar>(0) && 
		cCROSSap >= static_cast<scalar>(0);
}
}
}
}
}

#endif
