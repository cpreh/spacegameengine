#ifndef SGE_MATH_RECT_DETAIL_CONTAINS_POINT_HPP_INCLUDED
#define SGE_MATH_RECT_DETAIL_CONTAINS_POINT_HPP_INCLUDED

#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>

template<
	typename T,
	typename N,
	typename S
>
bool
sge::math::rect::contains_point(
	basic<T> const &r, 
	vector::basic<T, N, S> const &p)
{
	return p.x() >= r.left() && p.x() <= r.right() &&
	       p.y() >= r.top()  && p.y() <= r.bottom();
}

#endif
