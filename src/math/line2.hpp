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


#ifndef SGE_LINE2_HPP_INCLUDED
#define SGE_LINE2_HPP_INCLUDED

#include "vector.hpp"

namespace sge
{

template<typename T> class line2 {
public:
	typedef math::vector<T,2> point;
	line2(const point o, point d) : o(o), d(d) {}
	bool intersects(const line2& r) const
	{
		const T& a1 = d.x, a2 = d.y, a3 = r.d.x, a4 = r.d.y;
		return (a2*a3 - a1*a4);
	}
private:
	point o,d;
};

template<typename T> inline bool intersects(const line2<T>& l, const line2<T>& r)
{
	return l.intersects(r);
}

}

#endif
