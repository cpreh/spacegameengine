/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/math/rect/basic_decl.hpp>
#include <sge/math/rect/invalid.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/compare.hpp>
#include <sge/assign/make_array.hpp>
#include <functional>
#include <algorithm>

template<
	typename T
>
sge::math::rect::basic<T>::basic(
	value_type const &left_,
	value_type const &top_,
	value_type const &right_,
	value_type const &bottom_)
:
	rep(
		assign::make_array<
			T
		>(
			left_
		)(
			top_
		)(
			right_
		)(
			bottom_
		)
	)
{
	check();
}

template<
	typename T
>
sge::math::rect::basic<T>::basic(
	point_type const &pos,
	dim_type const &sz)
:
	rep(
		assign::make_array<
			T
		>(
			pos.x()
		)(
			pos.y()
		)(
			pos.x() + sz.w()
		)(
			pos.y() + sz.h()
		)
	)
{
	check();
}

template<
	typename T
>
sge::math::rect::basic<T> const
sge::math::rect::basic<T>::null()
{
	return basic(
		point_type::null(),
		dim_type::null()
	);
}

template<
	typename T
>
typename sge::math::rect::basic<T>::value_type
sge::math::rect::basic<T>::w() const
{
	return right() - left();
}

template<
	typename T
>
typename sge::math::rect::basic<T>::value_type
sge::math::rect::basic<T>::h() const
{
	return bottom() - top();
}

template<
	typename T
>
typename sge::math::rect::basic<T>::point_type const
sge::math::rect::basic<T>::pos() const
{
	return point_type(
		left(),
		top()
	);
}

template<
	typename T
>
sge::math::size_type
sge::math::rect::basic<T>::area() const
{
	return dim().content();
}

template<
	typename T
>
typename sge::math::rect::basic<T>::dim_type const
sge::math::rect::basic<T>::dim() const
{
	return dim_type(
		w(),
		h()
	);
}

template<
	typename T
>
typename sge::math::rect::basic<T>::value_type
sge::math::rect::basic<T>::left() const
{
	return rep[0];
}

template<
	typename T
>
typename sge::math::rect::basic<T>::value_type
sge::math::rect::basic<T>::top() const
{
	return rep[1];
}

template<
	typename T
>
typename sge::math::rect::basic<T>::value_type
sge::math::rect::basic<T>::right() const
{
	return rep[2];
}

template<
	typename T
>
typename sge::math::rect::basic<T>::value_type
sge::math::rect::basic<T>::bottom() const
{
	return rep[3];
}

template<
	typename T
>
void
sge::math::rect::basic<T>::left(
	value_type const nleft)
{
	rep[0] = nleft;
	check_w();
}

template<
	typename T
>
void
sge::math::rect::basic<T>::top(
	value_type const ntop)
{
	rep[1] = ntop;
	check_h();
}

template<
	typename T
>
void
sge::math::rect::basic<T>::right(
	value_type const nright)
{
	rep[2] = nright;
	check_w();
}

template<
	typename T
>
void
sge::math::rect::basic<T>::bottom(
	value_type const nbottom)
{
	rep[3] = nbottom;
	check_h();
}

template<
	typename T
>
bool
sge::math::rect::basic<T>::operator==(
	basic<T> const &r) const
{
	return std::equal(
		rep.begin(),
		rep.end(),
		r.rep.begin(),
		std::ptr_fun(
			sge::math::compare<T>
		)
	);
}

template<
	typename T
>
bool
sge::math::rect::basic<T>::operator!=(
	basic<T> const &r) const
{
	return !(*this == r);
}

template<
	typename T
>
void
sge::math::rect::basic<T>::check_w() const
{
	if (right() < left())
		throw_invalid();

}

template<
	typename T
>
void
sge::math::rect::basic<T>::check_h() const
{
	if(bottom() < top())
		throw_invalid();
}

template<
	typename T
>
void sge::math::rect::basic<T>::check() const
{
	check_w();
	check_h();
}

template<
	typename T
>
void
sge::math::rect::basic<T>::throw_invalid() const
{
	throw invalid(
		SGE_TEXT("Tried to create an invalid rectangle.")
	);
}

#endif
