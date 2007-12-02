/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MATH_RECT_IMPL_HPP_INCLUDED
#define SGE_MATH_RECT_IMPL_HPP_INCLUDED

#include <ostream>
#include "rect.hpp"

template<typename T>
sge::math::basic_rect<T>::basic_rect(const value_type& left_,
                                     const value_type& top_,
                                     const value_type& right_,
                                     const value_type& bottom_)
: left_(left_),
  top_(top_),
  right_(right_),
  bottom_(bottom_)
{}

template<typename T>
sge::math::basic_rect<T>::basic_rect(const point_type& pos,
                                     const dim_type& sz)
: left_(pos.x()),
  top_(pos.y()),
  right_(pos.x() + sz.w()),
  bottom_(pos.y() + sz.h())
{}

template<typename T>
typename sge::math::basic_rect<T>::value_type sge::math::basic_rect<T>::w() const
{
	return right() - left();
}

template<typename T>
typename sge::math::basic_rect<T>::value_type sge::math::basic_rect<T>::h() const
{
	return bottom() - top();
}

template<typename T>
typename sge::math::basic_rect<T>::point_type sge::math::basic_rect<T>::pos() const
{
	return point_type(left(), top());
}

template<typename T>
typename sge::math::basic_rect<T>::dim_type sge::math::basic_rect<T>::size() const
{
	return dim_type(w(), h());
}

template<typename T>
typename sge::math::basic_rect<T>::const_reference sge::math::basic_rect<T>::left() const
{
	return left_;
}

template<typename T>
typename sge::math::basic_rect<T>::const_reference sge::math::basic_rect<T>::top() const
{
	return top_;
}

template<typename T>
typename sge::math::basic_rect<T>::const_reference sge::math::basic_rect<T>::right() const
{
	return right_;
}

template<typename T>
typename sge::math::basic_rect<T>::const_reference sge::math::basic_rect<T>::bottom() const
{
	return bottom_;
}

template<typename T>
typename sge::math::basic_rect<T>::reference sge::math::basic_rect<T>::left()
{
	return left_;
}

template<typename T>
typename sge::math::basic_rect<T>::reference sge::math::basic_rect<T>::top()
{
	return top_;
}

template<typename T>
typename sge::math::basic_rect<T>::reference sge::math::basic_rect<T>::right()
{
	return right_;
}

template<typename T>
typename sge::math::basic_rect<T>::reference sge::math::basic_rect<T>::bottom()
{
	return bottom_;
}

template<typename T> 
sge::math::basic_rect<T> sge::math::operator+(const basic_rect<T>& l,
                                              const typename basic_rect<T>::point_type& r)
{
	return basic_rect<T>(l.left() + r.x(),
	                     l.top() + r.y(),
	                     l.right() + r.x(),
	                     l.bottom() + r.y());
}

template<typename T>
sge::math::basic_rect<T> sge::math::operator-(const basic_rect<T>& l,
                                              const typename basic_rect<T>::point_type& r)
{
	return basic_rect<T>(l.left() - r.x(),
	                     l.top() - r.y(),
	                     l.right() - r.x(),
	                     l.bottom - r.y());
}

template<typename T>
bool sge::math::operator==(const basic_rect<T>& l,
                           const basic_rect<T>& r)
{
	return l.left() == r.left()
	    && l.top() == r.top()
	    && l.right() == r.right()
	    && l.bottom() == r.bottom();
}

template<typename T>
bool sge::math::operator!=(const basic_rect<T>& l,
                           const basic_rect<T>& r)
{
	return !(l==r);
}

template<typename T>
sge::math::basic_rect<T> sge::math::resize_borders(const basic_rect<T>& r,
                                                   const T diff)
{
	return basic_rect<T>(r.left() + diff,
	                     r.top() + diff,
	                     r.right() - diff,
	                     r.bottom() - diff);
}

template<typename T, typename Ch, typename Traits>
std::basic_ostream<Ch,Traits>& sge::math::operator<<(std::basic_ostream<Ch,Traits>& s,
                                                     const basic_rect<T>& r)
{
	return s << s.widen('(')
			<< s.widen('(') << r.left() << s.widen(',') << r.top() << s.widen(')')
	         << s.widen(',')
	 		<< s.widen('(') << r.right() << s.widen(',') << r.bottom() << s.widen(')')
	         << s.widen(')');
}

#endif
