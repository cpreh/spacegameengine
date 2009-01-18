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


#ifndef SGE_MATH_DETAIL_STORAGE_DIM_HPP_INCLUDED
#define SGE_MATH_DETAIL_STORAGE_DIM_HPP_INCLUDED

#include <cstddef>

namespace sge
{
namespace math
{
namespace detail
{

template<
	typename T
>
typename T::size_type
storage_dim(
	T const &t)
{
	return t.size();
}

template<
	std::size_t N,
	typename T
>
std::size_t
storage_dim(
	T t[N])
{
	return N;
}

/*
template<
	typename T
>
struct storage_dim;

template<
	typename T,
	std::size_t M
>
struct storage_dim<
	T[M]
> {
	template<
		typename N,
		typename X
	>
	static N get(
		X)
	{
		return M;
	}
};

template<
	typename T,
	typename A
>
struct storage_dim<
	std::vector<
		T,
		A
	>
> {
	template<
		typename N
	>
	static N get(
		std::vector<
			T,
			A
		> const &v)
	{
		return v.size();
	}
};

template<
	typename T,
	typename N
>
struct storage_dim<
	view_storage<
		T,
		N
	>
> {
	template<
		typename N
	>
	static N get(
		view_storage<
			T,
			N
		> const &v)
	{
		return v.size();
	}
};
*/

}
}
}

#endif
