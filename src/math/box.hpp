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


#ifndef SGE_BOX_HPP_INCLUDED
#define SGE_BOX_HPP_INCLUDED

#include "./vector3.hpp"

namespace sge
{

template<typename T> struct box {
	typedef T value_type;
	box(const value_type& left = value_type(), const value_type& top = value_type(),
	    const value_type& right = value_type(), const value_type& bottom = value_type(),
	    const value_type& front = value_type(), const value_type& back = value_type())
		: left(left), top(top), right(right), bottom(bottom), front(front), back(back) {}
		value_type left, top, right, bottom, front, back;
};

template<typename T> inline bool operator==(const box<T>& l, const box<T>& r)
{
	return l.left == r.left && l.top == r.top && l.right == r.right && l.bottom == r.bottom && l.front == r.front && l.back == r.back;
}

template<typename T> inline bool operator!=(const box<T>& l, const box<T>& r)
{
	return !(l==r);
}

template<typename T> inline bool intersects(const box<T>& r, const vector3<T>& p)
{
	return p.x >= r.left && p.x <= r.right &&
	       p.y >= r.top  && p.y <= r.bottom &&
	       p.z >= r.front && p.z <= r.back;
}

}

#endif
