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


#ifndef SGE_LINE_SEG2_HPP_INCLUDED
#define SGE_LINE_SEG2_HPP_INCLUDED

#include "./vector2.hpp"
#include "./solve2.hpp"

namespace sge
{

template<typename T> class ray2;

template<typename T> class line_seg2 {
	friend class ray2<T>;
public:
	typedef basic_vector2<T> vec;
	line_seg2(vec p, vec q) : p(p), d(q-p) {}
	bool intersects(const line_seg2& r) const
	{
		T x1,x2;
		if(!solve2(d.x,d.y,-r.d.x,-r.d.y,r.p.x-p.x,r.p.y-p.y,x1,x2))
			return false;
		return !(x1 < 0 || x1 > 1 || x2 < 0 || x2 > 1);
	}
private:
	vec p,d;
};

template<typename T> inline bool intersects(const line_seg2<T>& l, const line_seg2<T>& r)
{
	return l.intersects(r);
}

}

#endif
