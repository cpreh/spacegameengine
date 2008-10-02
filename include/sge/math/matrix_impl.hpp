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

#include "matrix.hpp"
#include "compare.hpp"
#include "../algorithm/copy_n.hpp"
#include "../exception.hpp"
#include <algorithm>
#include <functional>
#include <ostream>

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
template<typename T, std::size_t N, std::size_t M>
template<typename... Args>
sge::math::basic_matrix<T, N, M>::basic_matrix(Args... args)
{
	set(args...);
}
#endif

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>::basic_matrix(no_initialization_tag)
{
}

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>::basic_matrix(const basic_matrix& r)
{
	copy_n(r.data_, size(), data_);
}

template<typename T, std::size_t N, std::size_t M>
typename sge::math::basic_matrix<T, N, M>&
sge::math::basic_matrix<T, N, M>::operator=(const basic_matrix& r)
{
	copy_n(r.data_, size(), data_);
	return *this;
}

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>&
sge::math::basic_matrix<T, N, M>::operator+=(const basic_matrix& r)
{
	for(size_type i = 0; i < size(); ++i)
		data_[i] += r.data_[i];
	return *this;
}

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>&
sge::math::basic_matrix<T, N, M>::operator-=(const basic_matrix& r)
{
	for(size_type i = 0; i < size(); ++i)
		data_[i] -= r.data_[i];
	return *this;
}

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>&
sge::math::basic_matrix<T, N, M>::operator*=(const value_type& v)
{
	for(size_type i = 0; i < size(); ++i)
		data_[i] *= v;
	return *this;
}

template<typename T, std::size_t N, std::size_t M>
const typename sge::math::basic_matrix<T, N, M>::proxy
sge::math::basic_matrix<T, N, M>::operator[](const size_type j)
{
	return proxy(j,data());
}

template<typename T, std::size_t N, std::size_t M>
const typename sge::math::basic_matrix<T, N, M>::const_proxy
sge::math::basic_matrix<T, N, M>::operator[](const size_type j) const
{
	return const_proxy(j,data());
}

template<typename T, std::size_t N, std::size_t M>
typename sge::math::basic_matrix<T, N, M>::pointer
sge::math::basic_matrix<T, N, M>::data()
{
	return data_;
}

template<typename T, std::size_t N, std::size_t M>
typename sge::math::basic_matrix<T, N, M>::const_pointer
sge::math::basic_matrix<T, N, M>::data() const
{
	return data_;
}

template<typename T, std::size_t N, std::size_t M>
typename sge::math::basic_matrix<T, N, M>::size_type
sge::math::basic_matrix<T, N, M>::size() const
{
	return Dim;
}

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
template<typename T, std::size_t N, std::size_t M>
template<typename... Args>
void sge::math::basic_matrix<T, N, M>::set(
	const_reference arg,
	Args... args)
{
	set_impl(0, arg, args...);
}

template<typename T, std::size_t N, std::size_t M>
template<typename... Args>
void sge::math::basic_matrix<T, N, M>::set_impl(
	const size_type i,
	const_reference arg,
	Args... args)
{
	at(i) = arg;
	set_impl(i+1, args...);
}

template<typename T, std::size_t N, std::size_t M>
void sge::math::basic_matrix<T, N, M>::set_impl(
	const size_type i,
	const_reference arg)
{
	at(i) = arg;
}

template<typename T, std::size_t N, std::size_t M>
typename sge::math::basic_matrix<T, N, M>::reference
sge::math::basic_matrix<T, N, M>::at(const size_type i)
{
	if(i >= Dim)
		throw exception(SGE_TEXT("basic_matrix<T, N, M>::at(): out of range!"));
	return data_[i];
}
#endif

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator+ (const basic_matrix<T,N,M>& r)
{
	basic_matrix<T,N,M> ret;
	for(typename basic_matrix<T,N,M>::size_type i = 0; i < r.size(); ++i)
		ret.data_[i] = +ret.data_[i];
	return ret;
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator- (const basic_matrix<T,N,M>& r)
{
	basic_matrix<T,N,M> ret;
	for(typename basic_matrix<T,N,M>::size_type i = 0; i < r.size(); ++i)
		ret.data_[i] = -ret.data_[i];
	return ret;
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator+ (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return basic_matrix<T,N,M>(l) += r;
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator- (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return basic_matrix<T,N,M>(l) -= r;
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator* (const typename basic_matrix<T,N,M>::value_type& l, const basic_matrix<T,N,M>& r)
{
	return basic_matrix<T,N,M>(r) *= l;
}

template<typename T, std::size_t N, std::size_t M1, std::size_t M2>
inline sge::math::basic_matrix<T,N,N> sge::math::operator* (const basic_matrix<T,M1,N>& a, const basic_matrix<T,N,M2>& b)
{
	typedef basic_matrix<T,M1,M2> result_type;
	result_type ret = result_type(no_initialization_tag());
	for(typename basic_matrix<T,M1,N>::size_type i = 0; i < M1; ++i)
		for(typename basic_matrix<T,N,M2>::size_type j = 0; j < M2; ++j)
		{
			typename result_type::value_type v(0);
			for(typename result_type::size_type r = 0; r < N; ++r)
				v += a[i][r] * b[r][j];
			ret[i][j] = v;
		}
	return ret;
}

template<typename T, std::size_t N, std::size_t M>
inline bool sge::math::operator== (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return std::equal(l.begin(), l.end(), r.begin(), std::ptr_fun(compare<T>));
}

template<typename T, std::size_t N, std::size_t M>
inline bool sge::math::operator!= (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return !(l==r);
}

template<typename T, std::size_t N, std::size_t M,typename Ch, typename Traits>
inline std::basic_ostream<Ch,Traits>& sge::math::operator<< (std::basic_ostream<Ch,Traits>& s, const basic_matrix<T,N,M>& m)
{
	s << s.widen('(');
	for(typename basic_matrix<T,N,M>::size_type j = 0; j < N; ++j)
	{
		s << s.widen('(');
		for(typename basic_matrix<T,N,M>::size_type i = 0; i < M; ++i)
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
inline sge::math::basic_matrix<T,N,N> sge::math::transpose(const basic_matrix<T,N,N>& m)
{
	basic_matrix<T,N,N> ret = basic_matrix<T,N,N>(no_initialization_tag());
	for(typename basic_matrix<T,N,N>::size_type j = 0; j < N; ++j)
		for(typename basic_matrix<T,N,N>::size_type i = 0; i < N; ++i)
			ret[i][j] = m[j][i];
	return ret;
}

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_vector<T,M>
sge::math::operator* (
	const basic_matrix<T,N,M>& m,
	const basic_vector<T,N>& v)
{
	typedef basic_vector<T,M> result_type;
	result_type ret;
	for(typename result_type::size_type i = 0; i < M; ++i)
		for(typename basic_matrix<T,N,M>::size_type j = 0; j < N; ++j)
			ret[i] += v[j] * m[j][i];
	return ret;
}

#endif
