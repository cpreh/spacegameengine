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

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <ostream>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/utility/enable_if.hpp>
#include "../types.hpp"
#include "../util.hpp"
#include "../exception.hpp"
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

	basic_matrix(no_initialization_tag)
	{
	}

	basic_matrix(const basic_matrix& r)
	{
		std::copy(r.data_,&r.data_[Dim],data_);
	}

	basic_matrix& operator=(const basic_matrix& r)
	{
		std::copy(r.data_,&r.data_[Dim],data_);
		return *this;
	}

	basic_matrix& operator+=(const basic_matrix& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] += r.data_[i];
		return *this;
	}

	basic_matrix& operator-=(const basic_matrix& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] -= r.data_[i];
		return *this;
	}

	basic_matrix& operator*=(const value_type& v)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] *= v;
		return *this;
	}

	proxy operator[](const size_type j)
	{
		return proxy(j,data());
	}

	const_proxy operator[](const size_type j) const
	{
		return const_proxy(j,data());
	}

	pointer data()
	{
		return data_;
	}

	const_pointer data() const
	{
		return data_;
	}

	size_type size() const
	{
		return Dim;
	}
private:
	value_type data_[Dim];
};

typedef basic_matrix<space_unit,4,4> space_matrix;

template<typename T, std::size_t N, std::size_t M>
inline basic_matrix<T,N,M> operator+ (const basic_matrix<T,N,M>& r)
{
	basic_matrix<T,N,M> ret;
	for(typename basic_matrix<T,N,M>::size_type i = 0; i < basic_matrix<T,N,M>::Dim; ++i)
		ret[i] = +ret[i];
	return ret;
}

template<typename T, std::size_t N, std::size_t M>
inline basic_matrix<T,N,M> operator- (const basic_matrix<T,N,M>& r)
{
	basic_matrix<T,N,M> ret;
	for(typename basic_matrix<T,N,M>::size_type i = 0; i < basic_matrix<T,N,M>::Dim; ++i)
		ret[i] = -ret[i];
	return ret;
}

template<typename T, std::size_t N, std::size_t M>
inline basic_matrix<T,N,M> operator+ (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return basic_matrix<T,N,M>(l) += r;
}

template<typename T, std::size_t N, std::size_t M>
inline basic_matrix<T,N,M> operator- (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return basic_matrix<T,N,M>(l) -= r;
}

template<typename T, std::size_t N, std::size_t M>
inline basic_matrix<T,N,M> operator* (const typename basic_matrix<T,N,M>::value_type& l, const basic_matrix<T,N,M>& r)
{
	return basic_matrix<T,N,M>(r) *= l;
}

template<typename T, std::size_t N1, std::size_t M1, std::size_t N2, std::size_t M2>
inline typename boost::enable_if_c<N1==M2, basic_matrix<T,N1,M2> >::type operator* (const basic_matrix<T,N1,M1>& a, const basic_matrix<T,N2,M2>& b)
{
//	basic_matrix<T,N1,M2> ret(no_initialization_tag());
	basic_matrix<T,N1,M2> ret = basic_matrix<T,N1,M2>(no_initialization_tag());
	for(typename basic_matrix<T,N1,M1>::size_type i = 0; i < M1; ++i)
		for(typename basic_matrix<T,N2,M2>::size_type j = 0; j < N2; ++j)
		{
			typename basic_matrix<T,N1,M2>::value_type v(0);
			for(typename basic_matrix<T,N1,M2>::size_type r = 0; r < N1; ++r)
				v += a[i][r] * b[r][j];
			ret[i][j] = v;
		}
	return ret;
}

/*template<typename T, std::size_t N, std::size_t M>
inline bool operator== (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	for(typename basic_matrix<T,N,M>::size_type x = 0; x < basic_matrix<T,N,M>::Dim; ++x)
		if(l.data[x] != r.data[x])
			return false;
	return true;
}

template<typename T, std::size_t N, std::size_t M>
inline bool operator!= (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return !(l==r);
}*/

template<typename T, std::size_t N, std::size_t M>
inline std::ostream& operator<< (std::ostream& s, const basic_matrix<T,N,M>& m)
{
	s << '(';
	for(typename basic_matrix<T,N,M>::size_type j = 0; j < N; ++j)
	{
		s << '(';
		for(typename basic_matrix<T,N,M>::size_type i = 0; i < M; ++i)
		{
			s << m[j][i];
			if(i != M-1)
				s << ',';
		}
		s << ')';
		if(j != N-1)
			s << ',';
	}
	s << ')';
	return s;
}

template<typename T, std::size_t N, std::size_t M>
inline std::wostream& operator<< (std::wostream& s, const basic_matrix<T,N,M>& m)
{
	s << L'(';
	for(typename basic_matrix<T,N,M>::size_type j = 0; j < N; ++j)
	{
		s << L'(';
		for(typename basic_matrix<T,N,M>::size_type i = 0; i < M; ++i)
		{
			s << m[j][i];
			if(i != M-1)
				s << L',';
		}
		s << L')';
		if(j != N-1)
			s << L',';
	}
	s << L')';
	return s;
}

template<typename T, std::size_t N>
inline basic_matrix<T,N,N> transpose(const basic_matrix<T,N,N>& m)
{
	basic_matrix<T,N,N> ret = basic_matrix<T,N,N>(no_initialization_tag());
	for(typename basic_matrix<T,N,N>::size_type j = 0; j < N; ++j)
		for(typename basic_matrix<T,N,N>::size_type i = 0; i < N; ++i)
			ret[i][j] = m[j][i];
	return ret;
}

inline space_matrix matrix_translation(const math::basic_vector<space_unit,3>& v)
{
	return space_matrix
	       (1, 0, 0, v.x(),
	        0, 1, 0, v.y(),
	        0, 0, 1, v.z(),
	        0, 0, 0, 1);

}

inline space_matrix matrix_translation(const space_unit x, const space_unit y, const space_unit z)
{
	return matrix_translation(math::basic_vector<space_unit,3>(x,y,z));
}

inline space_matrix matrix_scaling(const math::basic_vector<space_unit,3>& v)
{
	return space_matrix
	       (v.x(),     0,     0, 0,
	            0, v.y(),     0, 0,
	            0,     0, v.z(), 0,
	            0,     0,     0, 1);
}

inline space_matrix matrix_scaling(const space_unit x, const space_unit y, const space_unit z)
{
	return matrix_scaling(math::basic_vector<space_unit,3>(x,y,z));
}

#undef near
#undef far

inline space_matrix matrix_perspective(const space_unit aspect, const space_unit fov, const space_unit near, const space_unit far)
{
	if(far == near)
		throw exception("matrix_perspective(): far may not be near!");
	if(near == 0)
		throw exception("matrix_perspective(): near must not be 0!");
	const space_unit h = static_cast<space_unit>(1) / std::tan(fov / static_cast<space_unit>(2)),
	                 w = h / aspect,
	                 q = (far + near) / (far - near);
	return space_matrix
	       (w, 0,                     0, 0,
	        0, h,                     0, 0,
	        0, 0,                     q, 1,
	        0, 0, 2*far*near/(near-far), 0);
}

inline space_matrix matrix_orthogonal_xy()
{
	return space_matrix
	       (1,0,0,0,
	        0,1,0,0,
	        0,0,0,0,
	        0,0,0,1);
}

inline space_matrix matrix_rotation_z(const space_unit angle)
{
	const space_unit sinx = std::sin(angle),
	                 cosx = std::cos(angle);
	return space_matrix
	       (cosx, -sinx, 0, 0,
	        sinx,  cosx, 0, 0,
	        0,     0,    1, 0,
	        0,     0,    0, 1);
}

inline space_matrix matrix_rotation_y(const space_unit angle)
{
	const space_unit sinx = std::sin(angle),
	                 cosx = std::cos(angle);
	return space_matrix
	       (cosx, 0,-sinx, 0,
	        0,  1, 0, 0,
	        sinx,     0,    cosx, 0,
	        0,     0,    0, 1);
}

inline space_matrix matrix_rotation_x(const space_unit angle)
{
	const space_unit sinx = std::sin(angle),
	                 cosx = std::cos(angle);
	return space_matrix
	       (1,      0,    0, 0,
	        0,  cosx, -sinx, 0,
	        0,  sinx,  cosx, 0,
	        0,     0,     0, 1);
}

inline space_matrix matrix_identity()
{
	return space_matrix
	       (1,0,0,0,
	        0,1,0,0,
	        0,0,1,0,
	        0,0,0,1);
}

inline space_matrix matrix_orthogonal_xy(const space_unit left, const space_unit right, const space_unit top, const space_unit bottom, const space_unit near, const space_unit far)
{
	return space_matrix
	       (2/(right - left), 0, 0, -(right+left)/(right-left),
	        0, 2/(top - bottom), 0, -(top+bottom)/(top-bottom),
	        0, 0, (-2)/(far - near),-(far+near)/(far-near),
	        0, 0, 0, 1);
}

template<typename T, std::size_t NV, std::size_t N, std::size_t M>
inline typename boost::enable_if_c<NV==M, basic_vector<T,NV> >::type operator* (const basic_matrix<T,N,M>& m, const basic_vector<T,NV>& v)
{
	basic_vector<T,NV> ret;
	for(typename basic_vector<T,NV>::size_type i = 0; i < NV; ++i)
		for(typename basic_matrix<T,N,M>::size_type j = 0; j < M; ++j)
			ret[i] += v[j] * m[j][i];
	return ret;
}

}
}

#endif
