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

#include <cstddef>
#include <ostream>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include "../types.hpp"
#include "../util.hpp"
#include "matrix_proxy.hpp"
#include "vector.hpp"

#ifndef SGE_MATH_MATRIX_MAX_SIZE
#define SGE_MATH_MATRIX_MAX_SIZE 16
#endif

namespace sge
{
namespace math
{

template<typename T, std::size_t N, std::size_t M> class basic_matrix {
	enum { Dim = N*M };
	BOOST_STATIC_ASSERT(Dim > 1 && Dim <= SGE_MATH_MATRIX_MAX_SIZE);
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef std::size_t size_type;
	typedef detail::matrix_proxy_impl<value_type&, value_type*, N> proxy;
	typedef detail::matrix_proxy_impl<const value_type&, const value_type*, N> const_proxy;

#define SGE_MATH_MATRIX_CTOR_ASSIGN_N(z, n, text) data_[n] = text##n;
#define SGE_MATH_MATRIX_CTOR(z, n, text) basic_matrix(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_MATRIX_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_MATH_MATRIX_MAX_SIZE, SGE_MATH_MATRIX_CTOR, void)

	basic_matrix(no_initialization_tag);
	basic_matrix(const basic_matrix& r);
	basic_matrix& operator=(const basic_matrix& r);
	basic_matrix& operator+=(const basic_matrix& r);
	basic_matrix& operator-=(const basic_matrix& r);
	basic_matrix& operator*=(const value_type& v);
	const proxy operator[](const size_type j);
	const const_proxy operator[](const size_type j) const;
	pointer data();
	const_pointer data() const;
	size_type size() const;
private:
	value_type data_[Dim];
};

typedef basic_matrix<space_unit,4,4> space_matrix;

template<typename T, std::size_t N, std::size_t M>
basic_matrix<T,N,M> operator+ (const basic_matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
basic_matrix<T,N,M> operator- (const basic_matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
basic_matrix<T,N,M> operator+ (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
basic_matrix<T,N,M> operator- (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
basic_matrix<T,N,M> operator* (const typename basic_matrix<T,N,M>::value_type& l, const basic_matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M1, std::size_t M2>
basic_matrix<T,N,N> operator* (const basic_matrix<T,M1,N>& a, const basic_matrix<T,N,M2>& b);

template<typename T, std::size_t N, std::size_t M>
bool operator== (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M>
bool operator!= (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r);

template<typename T, std::size_t N, std::size_t M,typename Ch, typename Traits>
std::basic_ostream<Ch,Traits>& operator<< (std::basic_ostream<Ch,Traits>& s, const basic_matrix<T,N,M>& m);

template<typename T, std::size_t N>
basic_matrix<T,N,N> transpose(const basic_matrix<T,N,N>& m);

template<typename T, std::size_t N, std::size_t M>
basic_vector<T,M> operator* (const basic_matrix<T,N,M>& m, const basic_vector<T,N>& v);

space_matrix matrix_translation(const math::basic_vector<space_unit,3>& v);

space_matrix matrix_translation(const space_unit x, const space_unit y, const space_unit z);

space_matrix matrix_scaling(const math::basic_vector<space_unit,3>& v);

space_matrix matrix_scaling(const space_unit x, const space_unit y, const space_unit z);

space_matrix matrix_perspective(const space_unit aspect, const space_unit fov, const space_unit near, const space_unit far);

space_matrix matrix_orthogonal_xy();

space_matrix matrix_rotation_z(const space_unit angle);

space_matrix matrix_rotation_y(const space_unit angle);

space_matrix matrix_rotation_x(const space_unit angle);

space_matrix matrix_identity();

space_matrix matrix_orthogonal_xy(
	const space_unit left,
	const space_unit right,
	const space_unit top,
	const space_unit bottom,
	const space_unit near,
	const space_unit far);

}
}

#endif
