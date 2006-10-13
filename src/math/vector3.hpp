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


#ifndef SGE_VECTOR3_HPP_INCLUDED
#define SGE_VECTOR3_HPP_INCLUDED

#include <cmath>
#include <istream>
#include <ostream>

namespace sge
{

template<typename T> class vector3 {
public:
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	vector3(const_reference x = value_type(), const_reference y = value_type(), const_reference z = value_type())
		: x(x), y(y), z(z) {}

	vector3& operator+= (const vector3& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	}

	vector3& operator-= (const vector3& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}

	vector3& operator*= (const value_type& e)
	{
		x *= e;
		y *= e;
		z *= e;
		return *this;
	}

	vector3& normalize()
	{
		value_type l = length();
		(*this) *= (value_type(1) / l);
		return *this;
	}

	value_type length_quad() const
	{
		return x * x + y * y + z * z;
	}

	value_type length() const
	{
		return std::sqrt(length_quad());
	}

	value_type x,y,z;

};

template<typename T> inline vector3<T> normalize(const vector3<T>& r)
{
	return r.normalize();
}

template<typename T> inline vector3<T> operator+ (const vector3<T>& r)
{
	return vector3<T>( +r.x, +r.y, +r.z);
}

template<typename T> inline vector3<T> operator- (const vector3<T>& r)
{
	return vector3<T>( -r.x, -r.y, -r.z);
}

template<typename T> inline vector3<T> operator+ (const vector3<T>& l, const vector3<T>& r)
{
	return vector3<T>(l) += r;
}

template<typename T> inline vector3<T> operator- (const vector3<T>& l, const vector3<T>& r)
{
	return vector3<T>(l) -= r;
}

template<typename T> inline vector3<T> operator* (const T& l, const vector3<T>& r)
{
	return vector3<T>(r) *= l;
}

template<typename T> inline T dot_p(const vector3<T>& l, const vector3<T>& r)
{
	return l.x * r.x + l.y * r.y + l.z * r.z;
}

template<typename T> inline vector3<T> cross_p(const vector3<T>& l, const vector3<T>& r)
{
	return vector3<T>(l.y*r.z - l.z*r.y,
	                  l.z*r.x - l.x*r.z,
	                  l.x*r.y - l.y*r.x);
}

template<typename T> inline bool operator== (const vector3<T>& l, const vector3<T>& r)
{
	return l.x == r.x && l.y == r.y && l.z == r.z;
}

template<typename T> inline bool operator!= (const vector3<T>& l, const vector3<T>& r)
{
	return !(l==r);
}

template<typename T> inline bool operator< (const vector3<T>& l, const vector3<T>& r)
{
	return l.length_quad() < r.length_quad();
}

template<typename T> inline bool operator> (const vector3<T>& l, const vector3<T>& r)
{
	return l.length_quad() > r.length_quad();
}

template<typename T> inline bool operator<= (const vector3<T>& l, const vector3<T>& r)
{
	return l.length_quad() <= r.length_quad();
}

template<typename T> inline bool operator >= (const vector3<T>& l, const vector3<T>& r)
{
	return l.length_quad() >= r.length_quad();
}

template<typename T, typename Ch, typename Traits> inline std::basic_ostream<Ch,Traits>& operator<< (std::basic_ostream<Ch,Traits>& s, const vector3<T>& r)
{
	return s << '(' << r.x << ',' << r.y << ',' << r.z << ')';
}

template<typename T> inline T length_quad(const vector3<T>& l)
{
	return l.length_quad();
}

template<typename T> inline T length(const vector3<T>& l)
{
	return l.length();
}

}

#endif
