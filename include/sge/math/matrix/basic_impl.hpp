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


#ifndef SGE_MATH_MATRIX_IMPL_HPP_INCLUDED
#define SGE_MATH_MATRIX_IMPL_HPP_INCLUDED

#include "basic_decl.hpp"
#include "../compare.hpp"
#include "../detail/storage_data.hpp"
#include "../detail/make_variadic_constructor.hpp"
#include <sge/exception.hpp>
#include <algorithm>

template<
	typename T,
	typename N,
	typename M,
	typename S
>
sge::math::matrix::basic<T, N, M, S>::basic()
{}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
template<
	typename In
>
sge::math::matrix::basic<T, N, M, S>::basic(
	In const beg,
	In const end)
{
	std::copy(
		beg,
		end,
		data());
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::reference
sge::math::matrix::basic<T, N, M, S>::operator[](
	size_type const j)
{
	return reference(
		data() + j * N::value,
		M::value);
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::const_reference const
sge::math::matrix::basic<T, N, M, S>::operator[](
	size_type const j) const
{
	return const_reference(
		data() + j * N::value,
		M::value);
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::pointer
sge::math::matrix::basic<T, N, M, S>::data()
{
	return math::detail::storage_data(
		storage);
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::const_pointer
sge::math::matrix::basic<T, N, M, S>::data() const
{
	return const_cast<
		basic &
	>(
		*this).data();
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::size_type
sge::math::matrix::basic<T, N, M, S>::size() const
{
	return storage_dim(
		storage);
}

#if 0
template<typename T, std::size_t N, std::size_t M1, std::size_t M2>
inline sge::math::matrix<T,N,N> sge::math::operator* (const matrix<T,M1,N>& a, const matrix<T,N,M2>& b)
{
	typedef matrix<T,M1,M2> result_type;
	result_type ret;
	for(typename matrix<T,M1,N>::size_type i = 0; i < M1; ++i)
		for(typename matrix<T,N,M2>::size_type j = 0; j < M2; ++j)
		{
			typename result_type::value_type v(0);
			for(typename result_type::size_type r = 0; r < N; ++r)
				v += a[i][r] * b[r][j];
			ret[i][j] = v;
		}
	return ret;
}

template<typename T, std::size_t N>
inline sge::math::matrix<T,N,N> sge::math::transpose(const matrix<T,N,N>& m)
{
	matrix<T,N,N> ret;
	for(typename matrix<T,N,N>::size_type j = 0; j < N; ++j)
		for(typename matrix<T,N,N>::size_type i = 0; i < N; ++i)
			ret[i][j] = m[j][i];
	return ret;
}

}

#endif

#endif
