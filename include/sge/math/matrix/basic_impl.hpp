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
typename const sge::math::matrix::basic<T, N, M, S>::reference
sge::math::matrix::basic<T, N, M, S>::operator[](
	size_type const j)
{
	return reference(
		data() + j * N,
		M);
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename const sge::math::matrix::basic<T, N, M, S>::const_reference
sge::math::matrix::basic<T, N, M>::operator[](
	size_type const j) const
{
	return const_reference(
		data() + j * N,
		M);
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename const sge::math::matrix::basic<T, N, M, S>::reference
sge::math::matrix::basic<T, N, M, S>::at(
	size_type const j)
{
	SGE_ASSERT(j > M);
	return (*this)[j];
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename const sge::math::matrix::basic<T, N, M, S>::const_reference
sge::math::matrix::basic<T, N, M, S>::at(
	size_type const j) const
{
	SGE_ASSERT(j > M);
	return (*this)[j];
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::pointer
sge::math::matrix::basic<T, N, M>::data()
{
	return storage_data(
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
	return storage_data(
		storage);
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::pointer
sge::math::matrix::basic<T, N, M, S>::data_end()
{
	return data() + size();
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::const_pointer
sge::math::matrix<T, N, M>::data_end() const
{
	return data() + size();
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::iterator
sge::math::matrix::basic<T, N, M, S>::begin()
{
	return data();
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::const_iterator
sge::math::matrix::basic<T, N, M, S>::begin() const
{
	return data();
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::iterator
sge::math::matrix::basic<T, N, M, S>::end()
{
	return data_end();
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::const_iterator
sge::math::matrix::basic<T, N, M, S>::end() const
{
	return data_end();
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::reverse_iterator
sge::math::matrix::basic<T, N, M, S>::rbegin()
{
	return reverse_iterator(end());
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::const_reverse_iterator
sge::math::matrix::basic<T, N, M, S>::rbegin() const
{
	return reverse_iterator(end());
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::reverse_iterator
sge::math::matrix::basic<T, N, M, S>::rend()
{
	return reverse_iterator(begin());
}

template<
	typename T,
	typename N,
	typename M,
	typename S
>
typename sge::math::matrix::basic<T, N, M, S>::const_reverse_iterator
sge::math::matrix::basic<T, N, M, S>::rend() const
{
	return reverse_iterator(begin());
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

template<
	typename T,
	typename N,
	typename M,
	typename S
>
bool
sge::math::matrix::basic<T, N, M, S>::empty() const
{
	return size() == 0;
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
#endif

#if 0
template<typename T, std::size_t N, std::size_t M>
inline bool sge::math::operator== (const matrix<T,N,M>& l, const matrix<T,N,M>& r)
{
	return std::equal(l.begin(), l.end(), r.begin(), std::ptr_fun(compare<T>));
}

template<typename T, std::size_t N, std::size_t M>
inline bool sge::math::operator!= (const matrix<T,N,M>& l, const matrix<T,N,M>& r)
{
	return !(l==r);
}

template<typename T, std::size_t N, std::size_t M,typename Ch, typename Traits>
inline std::basic_ostream<Ch,Traits>& sge::math::operator<< (std::basic_ostream<Ch,Traits>& s, const matrix<T,N,M>& m)
{
	s << s.widen('(');
	for(typename matrix<T,N,M>::size_type j = 0; j < N; ++j)
	{
		s << s.widen('(');
		for(typename matrix<T,N,M>::size_type i = 0; i < M; ++i)
		{
			s << m[j][i];
			if(i != M-1)
				s << s.widen(',');
		}
		s << s.widen(')');
		if(j != N-1)
			s << s.widen(',');
	}
	return s << s.widen(')');
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

template<typename T, std::size_t N, std::size_t M>
sge::math::vector<T,M>
sge::math::operator* (
	const matrix<T,N,M>& m,
	const vector<T,N>& v)
{
	typedef vector<T,M> result_type;
	result_type ret(result_type::null());
	for(typename result_type::size_type i = 0; i < M; ++i)
		for(typename matrix<T,N,M>::size_type j = 0; j < N; ++j)
			ret[i] += v[j] * m[j][i];
	return ret;
}

}

#endif

#endif
