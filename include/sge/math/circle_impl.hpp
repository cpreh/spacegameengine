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


#ifndef SGE_MATH_CIRCLE_IMPL_HPP_INCLUDED
#define SGE_MATH_CIRCLE_IMPL_HPP_INCLUDED

#include "circle.hpp"

template<typename T>
sge::math::basic_circle<T>::basic_circle(
	const_reference x,
	const_reference y,
	const_reference radius_)
: origin_(x, y),
  radius_(radius_)
{}

template<typename T>
sge::math::basic_circle<T>::basic_circle(
	const point_type& origin_,
	const_reference radius_)
 : origin_(origin_),
   radius_(radius_)
{}

template<typename T>
typename sge::math::basic_circle<T>::point_type&
sge::math::basic_circle<T>::origin()
{
	return origin_;
}

template<typename T>
const typename sge::math::basic_circle<T>::point_type&
sge::math::basic_circle<T>::origin() const
{
	return origin_;
}

template<typename T>
typename sge::math::basic_circle<T>::reference
sge::math::basic_circle<T>::radius()
{
	return radius_;
}

template<typename T>
typename sge::math::basic_circle<T>::const_reference
sge::math::basic_circle<T>::radius() const
{
	return radius_;
}

template<typename T>
bool sge::math::intersects(
	basic_circle<T> const &a,
	basic_circle<T> const &b)
{
	return (a.origin() - b.origin()).length()
	< a.radius() + b.radius();
}

#endif
