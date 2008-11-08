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


#ifndef SGE_MATH_MATRIX_HPP_INCLUDED
#define SGE_MATH_MATRIX_HPP_INCLUDED

#include "../config.h"
#include "matrix_proxy.hpp"
#include "vector.hpp"
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#endif
#include <cstddef>
#include <iosfwd>

#ifndef SGE_MATH_MATRIX_MAX_SIZE
#define SGE_MATH_MATRIX_MAX_SIZE 16
#endif

namespace sge
{
namespace math
{

/**
 * matrix uses variadic templates where available
 *
 * \attention To use matrix' functions you have to include
 * <sge/math/matrix_impl.hpp>!
 */
template<typename T, std::size_t N, std::size_t M>
class matrix {
	enum { Dim = N*M };
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
	BOOST_STATIC_ASSERT(Dim > 1 && Dim <= SGE_MATH_MATRIX_MAX_SIZE);
#endif
public:
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef std::size_t size_type;
	typedef detail::matrix_proxy_impl<value_type&, value_type*, N> proxy;
	typedef detail::matrix_proxy_impl<const value_type&, const value_type*, N> const_proxy;

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	explicit matrix(Args... args);
#else
#define SGE_MATH_MATRIX_CTOR_ASSIGN_N(z, n, text) data_[n] = text##n;
#define SGE_MATH_MATRIX_CTOR(z, n, text) matrix(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_MATRIX_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_MATH_MATRIX_MAX_SIZE, SGE_MATH_MATRIX_CTOR, void)
#endif

	matrix();
	matrix& operator+=(const matrix& r);
	matrix& operator-=(const matrix& r);
	matrix& operator*=(const value_type& v);
	const proxy operator[](const size_type j);
	const const_proxy operator[](const size_type j) const;
	pointer data();
	const_pointer data() const;
	size_type size() const;
#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	void set(const_reference arg, Args... args);
private:
	template<typename... Args>
	void set_impl(size_type i, const_reference arg, Args... args);
	
	void set_impl(size_type i, const_reference arg);

	reference at(size_type);
#endif
private:
	value_type data_[Dim];
};

template<typename T, std::size_t N, std::size_t M>
matrix<T,N,M> operator+ (const matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
matrix<T,N,M> operator- (const matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
matrix<T,N,M> operator+ (const matrix<T,N,M>& l, const matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
matrix<T,N,M> operator- (const matrix<T,N,M>& l, const matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
matrix<T,N,M> operator* (const typename matrix<T,N,M>::value_type& l, const matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M1, std::size_t M2>
matrix<T,N,N> operator* (const matrix<T,M1,N>& a, const matrix<T,N,M2>& b);

template<typename T, std::size_t N, std::size_t M>
bool operator== (const matrix<T,N,M>& l, const matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
bool operator!= (const matrix<T,N,M>& l, const matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M,typename Ch, typename Traits>
std::basic_ostream<Ch,Traits>& operator<< (std::basic_ostream<Ch,Traits>& s, const matrix<T,N,M>& m);

template<typename T, std::size_t N>
matrix<T,N,N> transpose(const matrix<T,N,N>& m);

template<typename T, std::size_t N, std::size_t M>
vector<T,M> operator* (const matrix<T,N,M>& m, const vector<T,N>& v);

template<typename D, typename S, std::size_t N, std::size_t M>
matrix<D, N, M> const
structure_cast(
	matrix<S, N, M> const &s);

}
}

#endif
