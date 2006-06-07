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
