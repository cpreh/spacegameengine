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


#ifndef SGE_MATH_MATRIX_UTIL_HPP_INCLUDED
#define SGE_MATH_MATRIX_UTIL_HPP_INCLUDED

#include "basic_impl.hpp"
#include "static.hpp"
#include "../vector/basic_impl.hpp"
#include "../vector/static.hpp"

namespace sge
{
namespace math
{
namespace matrix
{
#if 0

template<
	typename T
>
matrix<T, 4, 4> const
matrix_translation(
	vector<T, 3> const &v);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_translation(
	T x,
	T y,
	T z);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_scaling(
	vector<T, 3> const &v);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_scaling(
	T x,
	T y,
	T z);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_perspective(
	T aspect,
	T fov,
	T near,
	T far);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_orthogonal_xy();

template<
	typename T
>
matrix<T, 2, 2> const
matrix_rotation_2d(
	T angle);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_rotation_z(
	T angle);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_rotation_y(
	T angle);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_rotation_x(
	T angle);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_identity();

template<
	typename T
>
matrix<T, 4, 4> const
matrix_orthogonal_xy(
	T left,
	T right,
	T top,
	T bottom,
	T near,
	T far);

template<
	typename T
>
matrix<T, 4, 4> const
matrix_orthogonal_xy(
	T left,
	T right,
	T top,
	T bottom);
#endif

}
}
}

//#include "detail/util_impl.hpp"

#endif
