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


#ifndef SGE_MATH_BOX_IMPL_HPP_INCLUDED
#define SGE_MATH_BOX_IMPL_HPP_INCLUDED

#include "box.hpp"

template<typename T>
sge::math::basic_box<T>::basic_box(const value_type& left_,
                                   const value_type& top_,
                                   const value_type& right_,
                                   const value_type& bottom_,
                                   const value_type& front_,
                                   const value_type& back_)
: left_(left_),
  top_(top_),
  right_(right_),
  bottom_(bottom_),
  front_(front_),
  back_(back_)
{}

template<typename T>
typename sge::math::basic_box<T>::value_type sge::math::basic_box<T>::w() const
{
	return right() - left();
}

template<typename T>
typename sge::math::basic_box<T>::value_type sge::math::basic_box<T>::h() const
{
	return bottom() - top();
}

template<typename T>
typename sge::math::basic_box<T>::value_type sge::math::basic_box<T>::size() const
{
	return w() * h() * d();
}

template<typename T>
typename sge::math::basic_box<T>::const_reference sge::math::basic_box<T>::left() const
{
	return left_;
}

template<typename T>
typename sge::math::basic_box<T>::const_reference sge::math::basic_box<T>::top() const
{
	return top_;
}

template<typename T>
typename sge::math::basic_box<T>::const_reference sge::math::basic_box<T>::right() const
{
	return right_;
}

template<typename T>
typename sge::math::basic_box<T>::const_reference sge::math::basic_box<T>::bottom() const
{
	return bottom_;
}

template<typename T>
typename sge::math::basic_box<T>::const_reference sge::math::basic_box<T>::front() const
{
	return front_;
}

template<typename T>
typename sge::math::basic_box<T>::const_reference sge::math::basic_box<T>::back() const
{
	return back_;
}

template<typename T>
typename sge::math::basic_box<T>::reference sge::math::basic_box<T>::left()
{
	return left_;
}

template<typename T>
typename sge::math::basic_box<T>::reference sge::math::basic_box<T>::top()
{
	return top_;
}

template<typename T>
typename sge::math::basic_box<T>::reference sge::math::basic_box<T>::right()
{
	return right_;
}

template<typename T>
typename sge::math::basic_box<T>::reference sge::math::basic_box<T>::bottom()
{
	return bottom_;
}

template<typename T>
typename sge::math::basic_box<T>::reference sge::math::basic_box<T>::front()
{
	return front_;
}

template<typename T>
typename sge::math::basic_box<T>::reference sge::math::basic_box<T>::back()
{
	return back_;
}

template<typename T>
bool sge::math::operator==(const basic_box<T>& l, const basic_box<T>& r)
{
	return l.left == r.left
	    && l.top == r.top
	    && l.right == r.right
	    && l.bottom == r.bottom
	    && l.front == r.front
	    && l.back == r.back;
}

template<typename T>
bool sge::math::operator!=(const basic_box<T>& l, const basic_box<T>& r)
{
	return !(l==r);
}

#endif
