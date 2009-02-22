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


#ifndef SGE_MATH_MATRIX_DETAIL_UTIL_IMPL_HPP_INCLUDED
#define SGE_MATH_MATRIX_DETAIL_UTIL_IMPL_HPP_INCLUDED

// TODO: fix this!

#include "../util.hpp"
#include "../basic_impl.hpp"
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <cmath>

#undef near
#undef far

template<
	typename T
>
sge::math::matrix<T, 4, 4> const
sge::math::matrix_perspective(
	T const aspect,
	T const fov,
	T const near,
	T const far)
{
	if(compare(far, near))
		throw exception(
			SGE_TEXT("matrix_perspective(): far may not be near!"));
	if(almost_zero(near))
		throw exception(
			SGE_TEXT("matrix_perspective(): near must not be 0!"));

	T const
		h = static_cast<T>(1) / std::tan(fov / static_cast<T>(2)),
		w = h / aspect,
		q = (far + near) / (far - near);
	return matrix<T, 4, 4>
	       (    w, static_cast<T>(0),                     static_cast<T>(0), static_cast<T>(0),
	        static_cast<T>(0),     h,                     static_cast<T>(0), static_cast<T>(0),
	        static_cast<T>(0), static_cast<T>(0),                         q, static_cast<T>(1),
	        static_cast<T>(0), static_cast<T>(0), static_cast<T>(2)*far*near/(near-far), static_cast<T>(0));
}

template<
	typename T
>
sge::math::matrix<T, 4, 4> const
sge::math::matrix_rotation_z(
	T const angle)
{
	T const
		sinx = std::sin(angle),
		cosx = std::cos(angle);
	return matrix<T, 4, 4>
	       (cosx,  -sinx, static_cast<T>(0), static_cast<T>(0),
	        sinx,   cosx, static_cast<T>(0), static_cast<T>(0),
	        static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
	        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}

template<
	typename T
>
sge::math::matrix<T, 4, 4> const sge::math::matrix_rotation_y(
	T const angle)
{
	T const
		sinx = std::sin(angle),
		cosx = std::cos(angle);
	return matrix<T, 4, 4>
	       ( cosx, static_cast<T>(0), -sinx, static_cast<T>(0),
	        static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
	         sinx, static_cast<T>(0),  cosx, static_cast<T>(0),
	        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}

template<
	typename T
>
sge::math::matrix<T, 4, 4> const
sge::math::matrix_rotation_x(
	T const angle)
{
	T const
		sinx = std::sin(angle),
		cosx = std::cos(angle);
	return matrix<T, 4, 4>
	       (static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
	        static_cast<T>(0),  cosx, -sinx, static_cast<T>(0),
	        static_cast<T>(0),  sinx,  cosx, static_cast<T>(0),
	        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}

template<
	typename T
>
sge::math::matrix<T, 4, 4> const
sge::math::matrix_orthogonal_xy(
	T const left,
	T const right,
	T const top,
	T const bottom,
	T const near,
	T const far)
{
	return matrix<T, 4, 4>
	       (static_cast<T>(2)/(right - left), static_cast<T>(0),                static_cast<T>(0), -(right+left)/(right-left),
	        static_cast<T>(0),                static_cast<T>(2)/(top - bottom), static_cast<T>(0), -(top+bottom)/(top-bottom),
	        static_cast<T>(0),                static_cast<T>(0),                static_cast<T>(-2)/(far - near), -(far+near)/(far-near),
	        static_cast<T>(0),                static_cast<T>(0),                static_cast<T>(0), static_cast<T>(1));
}

template<
	typename T
>
sge::math::matrix<T, 4, 4> const
sge::math::matrix_orthogonal_xy(
	T const left,
	T const right,
	T const top,
	T const bottom)
{
	return matrix<T, 4, 4>
	       (static_cast<T>(2)/(right - left),                static_cast<T>(0),static_cast<T>(0), -(right+left)/(right-left),
	                       static_cast<T>(0), static_cast<T>(2)/(top - bottom),static_cast<T>(0), -(top+bottom)/(top-bottom),
	                       static_cast<T>(0),                static_cast<T>(0),static_cast<T>(0), static_cast<T>(0),
	                       static_cast<T>(0),                static_cast<T>(0),static_cast<T>(0), static_cast<T>(1));
}

#endif
