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


#ifndef SGE_RAY2_HPP_INCLUDED
#define SGE_RAY2_HPP_INCLUDED

#include "./vector2.hpp"
#include "./solve2.hpp"
#include "./line_seg2.hpp"

namespace sge
{
template<typename T> class ray2 {
public:
	typedef vector<T,2> vec;
	ray2(vec o, vec d) : o(o), d(d) {}
	bool intersection(const line_seg2<T>& r, vec& v) const 
	{
		T x1,x2;
		if(!solve2(d.x,d.y,-r.d.x,-r.d.y,r.p.x-o.x,r.p.y-o.y,x1,x2))
			return false;
		if(x1 < 0 || x2 < 0 || x2 > 1)
			return false;
		v = vec(o.x + x1*d.x, o.y + x1*d.y);
		return true;
	}
private:
	vec o,d;
};

template<typename T> inline bool intersection(const ray2<T>& l, const line_seg2<T>& r, typename ray2<T>::vec& v)
{
	return l.intersection(r,v);
}

}

#endif
