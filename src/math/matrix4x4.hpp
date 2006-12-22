/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_MATRIX4X4_HPP_INCLUDED
#define SGE_MATRIX4X4_HPP_INCLUDED

#include <cmath>
#include <ostream>
#include <cstddef>
#include <stdexcept>
#include "./vector3.hpp"
#include "./matrix_proxy.hpp"

namespace sge
{

struct no_initialization_tag {};

template<typename T> class matrix4x4 {
public:
	typedef T           value_type;
	typedef std::size_t size_type;
	static const size_type stride = 4;
	typedef detail::matrix_proxy_impl<value_type&, value_type*, stride> proxy;
	typedef detail::matrix_proxy_impl<const value_type&, const value_type*, stride> const_proxy;

	matrix4x4(no_initialization_tag) {}

	matrix4x4()
	: m_00(1), m_10(0), m_20(0), m_30(0),
	  m_01(0), m_11(1), m_21(0), m_31(0),
	  m_02(0), m_12(0), m_22(1), m_32(0),
	  m_03(0), m_13(0), m_23(0), m_33(1) {}

	matrix4x4(const value_type& _00, const value_type& _10, const value_type& _20, const value_type& _30,
	          const value_type& _01, const value_type& _11, const value_type& _21, const value_type& _31,
	          const value_type& _02, const value_type& _12, const value_type& _22, const value_type& _32,
	          const value_type& _03, const value_type& _13, const value_type& _23, const value_type& _33)
		: m_00(_00), m_10(_10), m_20(_20), m_30(_30),
		  m_01(_01), m_11(_11), m_21(_21), m_31(_31),
		  m_02(_02), m_12(_12), m_22(_22), m_32(_32),
		  m_03(_03), m_13(_13), m_23(_23), m_33(_33) {}

	matrix4x4& operator+= (const matrix4x4& r)
	{
		m_00 += r.m_00; m_10 += r.m_10; m_20 += r.m_20; m_30 += r.m_30;
		m_01 += r.m_01; m_11 += r.m_11; m_21 += r.m_21; m_31 += r.m_31;
		m_02 += r.m_02; m_12 += r.m_12; m_22 += r.m_21; m_32 += r.m_32;
		m_03 += r.m_03; m_13 += r.m_13; m_23 += r.m_22; m_33 += r.m_33;
		return *this;
	}

	matrix4x4& operator-= (const matrix4x4& r)
	{
		m_00 -= r.m_00; m_10 -= r.m_10; m_20 -= r.m_20; m_30 -= r.m_30;
		m_01 -= r.m_01; m_11 -= r.m_11; m_21 -= r.m_21; m_31 -= r.m_31;
		m_02 -= r.m_02; m_12 -= r.m_12; m_22 -= r.m_21; m_32 -= r.m_32;
		m_03 -= r.m_03; m_13 -= r.m_13; m_23 -= r.m_22; m_33 -= r.m_33;
		return *this;
	}

	matrix4x4& operator*= (const matrix4x4& r)
	{
		matrix4x4 l = *this;
		m_00 = r.m_00 * l.m_00 + r.m_10 * l.m_01 + r.m_20 * l.m_02 + r.m_30 * l.m_03;
		m_01 = r.m_01 * l.m_00 + r.m_11 * l.m_01 + r.m_21 * l.m_02 + r.m_31 * l.m_03;
		m_02 = r.m_02 * l.m_00 + r.m_12 * l.m_01 + r.m_22 * l.m_02 + r.m_32 * l.m_03;
		m_03 = r.m_03 * l.m_00 + r.m_13 * l.m_01 + r.m_23 * l.m_02 + r.m_33 * l.m_03;
		m_10 = r.m_00 * l.m_10 + r.m_10 * l.m_11 + r.m_20 * l.m_12 + r.m_30 * l.m_13;
		m_11 = r.m_01 * l.m_10 + r.m_11 * l.m_11 + r.m_21 * l.m_12 + r.m_31 * l.m_13;
		m_12 = r.m_02 * l.m_10 + r.m_12 * l.m_11 + r.m_22 * l.m_12 + r.m_32 * l.m_13;
		m_13 = r.m_03 * l.m_10 + r.m_13 * l.m_11 + r.m_23 * l.m_12 + r.m_33 * l.m_13;
		m_20 = r.m_00 * l.m_20 + r.m_10 * l.m_21 + r.m_20 * l.m_22 + r.m_30 * l.m_23;
		m_21 = r.m_01 * l.m_20 + r.m_11 * l.m_21 + r.m_21 * l.m_22 + r.m_31 * l.m_23;
		m_22 = r.m_02 * l.m_20 + r.m_12 * l.m_21 + r.m_22 * l.m_22 + r.m_32 * l.m_23;
		m_23 = r.m_03 * l.m_20 + r.m_13 * l.m_21 + r.m_23 * l.m_22 + r.m_33 * l.m_23;
		m_30 = r.m_00 * l.m_30 + r.m_10 * l.m_31 + r.m_20 * l.m_32 + r.m_30 * l.m_33;
		m_31 = r.m_01 * l.m_30 + r.m_11 * l.m_31 + r.m_21 * l.m_32 + r.m_31 * l.m_33;
		m_32 = r.m_02 * l.m_30 + r.m_12 * l.m_31 + r.m_22 * l.m_32 + r.m_32 * l.m_33;
		m_33 = r.m_03 * l.m_30 + r.m_13 * l.m_31 + r.m_23 * l.m_32 + r.m_33 * l.m_33;
		return *this;
	}

	matrix4x4& operator*= (const value_type& e)
	{
		m_01 *= e; m_10 *= e; m_20 *= e; m_30 *= e;
		m_01 *= e; m_11 *= e; m_21 *= e; m_31 *= e;
		m_02 *= e; m_12 *= e; m_22 *= e; m_32 *= e;
		m_03 *= e; m_13 *= e; m_23 *= e; m_33 *= e;
		return *this;
	}

	proxy operator[](size_type x) { return proxy(x,&m_00); }
	const_proxy operator[](size_type x) const { return const_proxy(x,&m_00); }
private:
	value_type m_00, m_10, m_20, m_30,
	           m_01, m_11, m_21, m_31,
	           m_02, m_12, m_22, m_32,
	           m_03, m_13, m_23, m_33;
};

template<typename T> inline matrix4x4<T> operator+ (const matrix4x4<T>& r)
{
	return matrix4x4<T>(+r[0][0], +r[1][0], +r[2][0], +r[3][0],
	                    +r[0][1], +r[1][1], +r[2][1], +r[3][1],
	                    +r[0][2], +r[1][2], +r[2][2], +r[3][2],
	                    +r[0][3], +r[1][3], +r[2][3], +r[3][3]);
}

template<typename T> inline matrix4x4<T> operator- (const matrix4x4<T>& r)
{
	return matrix4x4<T>(-r[0][0], -r[1][0], -r[2][0], -r[3][0],
	                    -r[0][1], -r[1][1], -r[2][1], -r[3][1],
	                    -r[0][2], -r[1][2], -r[2][2], -r[3][2],
	                    -r[0][3], -r[1][3], -r[2][3], -r[3][3]);
}

template<typename T> inline matrix4x4<T> operator+ (const matrix4x4<T>& l, const matrix4x4<T>& r)
{
	return matrix4x4<T>(l) += r;
}

template<typename T> inline matrix4x4<T> operator- (const matrix4x4<T>& l, const matrix4x4<T>& r)
{
	return matrix4x4<T>(l) -= r;
}

template<typename T> inline matrix4x4<T> operator* (const matrix4x4<T>& l, const matrix4x4<T>& r)
{
	return matrix4x4<T>(l) *= r;
}

template<typename T> inline matrix4x4<T> operator* (const matrix4x4<T>& l, const T& r)
{
	return matrix4x4<T>(l) *= r;
}

template<typename T> inline bool operator== (const matrix4x4<T>& l, const matrix4x4<T>& r)
{
	return (l[0][0] == r[0][0] && l[0][1] == r[0][1] && l[0][2] == r[0][2] && l[0][3] == r[0][3] &&
	        l[1][0] == r[1][0] && l[1][1] == r[1][1] && l[1][2] == r[1][2] && l[1][3] == r[1][3] &&
	        l[2][0] == r[2][0] && l[2][1] == r[2][1] && l[2][2] == r[2][2] && l[2][3] == r[2][3] &&
	        l[3][0] == r[3][0] && l[3][1] == r[3][1] && l[3][2] == r[3][2] && l[3][3] == r[3][3]);
}

template<typename T> inline bool operator!= (const matrix4x4<T>& l, const matrix4x4<T>& r)
{
	return !(l==r);
}

template<typename T> inline std::ostream& operator<< (std::ostream& s, const matrix4x4<T>& m)
{
	s << '(' << m[0][0] << ',' << m[1][0] << ',' << m[2][0] << ',' << m[3][0] << ')' << '\n'
	  << '(' << m[0][1] << ',' << m[1][1] << ',' << m[2][1] << ',' << m[3][1] << ')' << '\n'
	  << '(' << m[0][2] << ',' << m[1][2] << ',' << m[2][2] << ',' << m[3][2] << ')' << '\n'
	  << '(' << m[0][3] << ',' << m[1][3] << ',' << m[2][3] << ',' << m[3][3] << ')';
	return s;
}

template<typename T> inline T det(const matrix4x4<T>& r)
{
	return r[0][0] * (r[1][1] * r[2][2] - r[1][2] * r[2][1]) -
	       r[0][1] * (r[1][0] * r[2][2] - r[1][2] * r[2][0]) +
	       r[0][2] * (r[1][0] * r[2][1] - r[1][1] * r[2][0]);
}

template<typename T> inline matrix4x4<T> inverse(const matrix4x4<T>& r)
{
	const T d = det(r);
	if(d == 0) 
		throw std::runtime_error("inverse(matrix4x4): matrix does not have an inverse!");

	const T inv_d = T(1) / d;
	matrix4x4<T> ret = matrix4x4<T>(no_initialization_tag());
	ret[0][0] =  inv_d * (r[1][1] * r[2][2] - r[1][2] * r[2][1]);
	ret[0][1] = -inv_d * (r[0][1] * r[2][2] - r[0][2] * r[2][1]);
	ret[0][2] =  inv_d * (r[0][1] * r[1][2] - r[0][2] * r[1][1]);
	ret[0][3] =  0;
	ret[1][0] = -inv_d * (r[1][0] * r[2][2] - r[1][2] * r[2][0]);
	ret[1][1] =  inv_d * (r[0][0] * r[2][2] - r[0][2] * r[2][0]);
	ret[1][2] = -inv_d * (r[0][0] * r[1][2] - r[0][2] * r[1][0]);
	ret[1][3] =  0;
	ret[2][0] =  inv_d * (r[1][0] * r[2][1] - r[1][1] * r[2][0]);
	ret[2][1] = -inv_d * (r[0][0] * r[2][1] - r[0][1] * r[2][0]);
	ret[2][2] =  inv_d * (r[0][0] * r[1][1] - r[0][1] * r[1][1]);
	ret[2][3] =  0;
	ret[3][0] = -(r[3][0] * ret[0][0] + r[3][1] * ret[1][0] + r[3][2] * ret[2][0]);
	ret[3][1] = -(r[3][0] * ret[0][1] + r[3][1] * ret[1][1] + r[3][2] * ret[2][1]);
	ret[3][2] = -(r[3][0] * ret[0][2] + r[3][1] * ret[1][2] + r[3][2] * ret[2][2]);
	ret[3][3] =  T(1);
	return ret;
}

template<typename T> inline matrix4x4<T> matrix_translation(const math::vector<T,3>& v)
{
	return matrix4x4<T>(    1,     0,     0, 0,
	                        0,     1,     0, 0,
	                        0,     0,     1, 0,
	                    v.x(), v.y(), v.z(), 1);
}

template<typename T> inline matrix4x4<T> matrix_translation(const T& x, const T& y, const T& z)
{
	return matrix_translation<T>(math::vector<T,3>(x,y,z));
}

template<typename T> inline matrix4x4<T> matrix_scaling(const math::vector<T,3>& v)
{
	return matrix4x4<T>(v.x(),     0,     0, 0,
	                        0, v.y(),     0, 0,
	                        0,     0, v.z(), 0,
	                        0,     0,     0, 1);
}

template<typename T> inline matrix4x4<T> matrix_scaling(const T& x, const T& y, const T& z)
{
	return matrix_scaling<T>(math::vector<T,3>(x,y,z));
}

template<typename T> inline matrix4x4<T> matrix_transpose(const matrix4x4<T>& m)
{
	return matrix4x4<T>(m[0][0], m[0][1], m[0][2], m[0][3],
	                    m[1][0], m[1][1], m[1][2], m[1][3],
	                    m[2][0], m[2][1], m[2][2], m[2][3],
	                    m[3][0], m[3][1], m[3][2], m[3][3]);
}

template<typename T> inline matrix4x4<T> matrix_look_at(const math::vector<T,3>& eye,
                                                        const math::vector<T,3>& at,
                                                        const math::vector<T,3>& up)
{
	using namespace math;
	const math::vector<T,3> zaxis = normalize(at - eye),
	                        xaxis = normalize(cross_product(up, zaxis)),
	                        yaxis = cross(zaxis, xaxis);

	return matrix4x4<T>(xaxis.x,          yaxis.x,          zaxis.x,          0,
	                    xaxis.y,          yaxis.y,          zaxis.y,          0,
	                    xaxis.z,          yaxis.z,          zaxis.z,          0,
	                    -dot(xaxis,eye),  -dot(yaxis,eye),  -dot(zaxis,eye),  1);
}

#undef near
#undef far

template<typename T> inline matrix4x4<T> matrix_perspective(const T& aspect, const T& fov, const T& near, const T& far)
{
	const T h = T(1) / std::tan(fov / T(2)),
	        w = h * aspect,
	        q = far / (far - near);
	return matrix4x4<T>(w, 0, 0, 0,
	                    0, h, 0, 0,
	                    0, 0, q, 1,
	                    0, 0, -q*near, 0);
}

template<typename T> inline matrix4x4<T> matrix_orthogonal_xy()
{
	return matrix4x4<T>(1,0,0,0,
	                    0,1,0,0,
	                    0,0,0,0,
	                    0,0,0,1);
}

template<typename T> inline matrix4x4<T> matrix_rotation_z(const T& angle)
{
	const T sinx = std::sin(angle),
	        cosx = std::cos(angle);
	return matrix4x4<T>(cosx, -sinx, 0, 0,
	                    sinx,  cosx, 0, 0,
			       0,     0, 1, 0,
	                       0,     0, 0, 1);
}


}

#endif
