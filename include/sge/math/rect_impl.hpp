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

#include <sge/math/rect_decl.hpp>
#include <sge/math/compare.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/structure_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <ostream>

template<typename T>
sge::math::rect<T>::rect(
	value_type const &left_,
	value_type const &top_,
	value_type const &right_,
	value_type const &bottom_)
:
	left_(left_),
	top_(top_),
	right_(right_),
	bottom_(bottom_)
{
	check();
}

template<typename T>
sge::math::rect<T>::rect(
	point_type const &pos,
	dim_type const &sz)
:
	left_(pos.x()),
	top_(pos.y()),
	right_(pos.x() + sz.w()),
	bottom_(pos.y() + sz.h())
{
	check();
}

template<typename T>
sge::math::rect<T>::rect(
	dim_type const &sz)
:
	left_(
		static_cast<value_type>(0)),
	top_(
		static_cast<value_type>(0)),
	right_(sz.w()),
	bottom_(sz.h())
{
	check();
}

template<typename T>
sge::math::rect<T> const sge::math::rect<T>::null()
{
	return rect(point_type::null(),dim_type::null());
}

template<typename T>
typename sge::math::rect<T>::value_type sge::math::rect<T>::w() const
{
	return right() - left();
}

template<typename T>
typename sge::math::rect<T>::value_type sge::math::rect<T>::h() const
{
	return bottom() - top();
}

template<typename T>
typename sge::math::rect<T>::point_type const
sge::math::rect<T>::pos() const
{
	return point_type(left(), top());
}

template<typename T>
typename sge::math::rect<T>::size_type
sge::math::rect<T>::area() const
{
	return dim().content();
}

template<typename T>
typename sge::math::rect<T>::dim_type const
sge::math::rect<T>::dim() const
{
	return dim_type(w(), h());
}

template<typename T>
typename sge::math::rect<T>::const_reference
sge::math::rect<T>::left() const
{
	return left_;
}

template<typename T>
typename sge::math::rect<T>::const_reference
sge::math::rect<T>::top() const
{
	return top_;
}

template<typename T>
typename sge::math::rect<T>::const_reference
sge::math::rect<T>::right() const
{
	return right_;
}

template<typename T>
typename sge::math::rect<T>::const_reference
sge::math::rect<T>::bottom() const
{
	return bottom_;
}

template<typename T>
typename sge::math::rect<T>::reference
sge::math::rect<T>::left()
{
	return left_;
}

template<typename T>
typename sge::math::rect<T>::reference
sge::math::rect<T>::top()
{
	return top_;
}

template<typename T>
typename sge::math::rect<T>::reference
sge::math::rect<T>::right()
{
	return right_;
}

template<typename T>
typename sge::math::rect<T>::reference
sge::math::rect<T>::bottom()
{
	return bottom_;
}

template<typename T>
void sge::math::rect<T>::check()
{
	if (right() < left() || bottom() < top())
		throw exception(SGE_TEXT("tried to create a rectangle ")+
			boost::lexical_cast<string>(*this)+SGE_TEXT(" which is invalid"));
}

template<typename T> 
sge::math::rect<T> const sge::math::operator+(
	rect<T> const &l,
	typename rect<T>::point_type const & r)
{
	return rect<T>(l.left() + r.x(),
	                     l.top() + r.y(),
	                     l.right() + r.x(),
	                     l.bottom() + r.y());
}

template<typename T>
sge::math::rect<T> const
sge::math::operator-(
	rect<T> const &l,
	typename rect<T>::point_type const &r)
{
	return rect<T>(l.left() - r.x(),
	                     l.top() - r.y(),
	                     l.right() - r.x(),
	                     l.bottom - r.y());
}

template<typename T>
bool sge::math::operator==(const rect<T>& l,
                           const rect<T>& r)
{
	return compare(l.left(),r.left())
	    && compare(l.top(),r.top())
	    && compare(l.right(),r.right())
	    && compare(l.bottom(),r.bottom());
}

template<typename T>
bool sge::math::operator!=(const rect<T>& l,
                           const rect<T>& r)
{
	return !(l==r);
}

template<typename T>
sge::math::rect<T> const
sge::math::resize_borders(
	const rect<T>& r,
	const T diff)
{
	return rect<T>(
		r.left() + diff,
		r.top() + diff,
		r.right() - diff,
		r.bottom() - diff);
}

template<typename T, typename Ch, typename Traits>
std::basic_ostream<Ch,Traits>& sge::math::operator<<(std::basic_ostream<Ch,Traits>& s,
                                                     const rect<T>& r)
{
	return s
		<< s.widen('(')
			<< s.widen('(') << r.left() << s.widen(',') << r.top() << s.widen(')')
		<< s.widen(',')
	 		<< s.widen('(') << r.right() << s.widen(',') << r.bottom() << s.widen(')')
		<< s.widen(')');
}

template<
	typename D,
	typename S
>
D const
sge::math::structure_cast(
	rect<S> const &r)
{
	return D(
		sge::structure_cast<
			typename D::point_type
		>(
			r.pos()),
		sge::structure_cast<
			typename D::dim_type
		>(
			r.dim()));
}

#endif
