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


#ifndef SGE_SOLVE2_HPP_INCLUDED
#define SGE_SOLVE2_HPP_INCLUDED

namespace sge
{

template<typename T> inline T determinant2(const T& a1, const T& a2, const T& a3, const T& a4)
{
	return a1*a4 - a2*a3;
}

template<typename T> inline bool solve2(const T& a1, const T& a2, const T& a3, const T& a4, const T& r1, const T& r2, T& x1, T& x2)
{
	const T det = determinant2(a1,a2,a3,a4);
	if(det==0)
		return false;
	x1 = (a4*r1 - a3*r2) / det;
	x2 = (a1*r2 - a2*r1) / det;
	return true;
}

}

#endif
