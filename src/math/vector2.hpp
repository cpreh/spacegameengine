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


#ifndef SGE_VECTOR2_HPP_INCLUDED
#define SGE_VECTOR2_HPP_INCLUDED

#include "../types.hpp"
#include <cmath>
#include <istream>
#include <ostream>

namespace sge
{

template<typename T> class basic_vector2 {
public:
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	basic_vector2(const_reference nx = value_type(), const_reference ny = value_type()) : x(nx), y(ny) {}

	basic_vector2& operator+= (const basic_vector2& r)
	{
		x += r.x;
		y += r.y;
		return *this;
	}

	basic_vector2& operator-= (const basic_vector2& r)
	{
		x -= r.x;
		y -= r.y;
		return *this;
	}

	basic_vector2& operator*= (const value_type& e)
	{
		x *= e;
		y *= e;
		return *this;
	}

	basic_vector2& normalize()
	{
		value_type l = length();
		(*this) *= T(1) / l;
		return *this;
	}

	value_type length_quad() const
	{
		return x * x + y * y;
	}

	value_type length() const
	{
		return std::sqrt(length_quad());
	}
	value_type x,y;
};

template<typename T> inline basic_vector2<T> normalize(const basic_vector2<T>& r)
{
	return r.normalize();
}

template<typename T> inline basic_vector2<T> operator+ (const basic_vector2<T>& r)
{
	return basic_vector2<T>( +r.x, +r.y);
}

template<typename T> inline basic_vector2<T> operator- (const basic_vector2<T>& r)
{
	return basic_vector2<T>( -r.x, - r.y);
}

template<typename T> inline basic_vector2<T> operator+ (const basic_vector2<T>& l, const basic_vector2<T>& r)
{
	return basic_vector2<T>(l) += r;
}

template<typename T> inline basic_vector2<T> operator- (const basic_vector2<T>& l, const basic_vector2<T>& r)
{
	return  basic_vector2<T>(l) -= r;
}

template<typename T> inline basic_vector2<T> operator* (const T& l, const basic_vector2<T>& r)
{
	return  basic_vector2<T>(r) *= l;
}

template<typename T> inline T dot_product (const basic_vector2<T>& l, const basic_vector2<T>& r)
{
	return basic_vector2<T>(l.x * r.x, l.y * r.y);
}

template<typename T> inline bool operator== (const basic_vector2<T>& l, const basic_vector2<T>& r)
{
	return (l.x == r.x && l.y == r.y);
}

template<typename T> inline bool operator!= (const basic_vector2<T>& l, const basic_vector2<T>& r)
{
	return !(l==r);
}

template<typename T> inline bool operator< (const basic_vector2<T>& l, const basic_vector2<T>& r)
{
	return l.length_quad() < r.length_quad();
}

template<typename T> inline bool operator> (const basic_vector2<T>& l, const basic_vector2<T>& r)
{
	return l.length_quad() > r.length_quad();
}

template<typename T> inline bool operator<= (const basic_vector2<T>& l, const basic_vector2<T>& r)
{
	return l.length_quad() <= r.length_quad();
}

template<typename T> inline bool operator >= (const basic_vector2<T>& l, const basic_vector2<T>& r)
{
	return l.length_quad() >= r.length_quad();
}

template<typename T, typename Ch, typename Traits> inline std::basic_ostream<Ch,Traits>& operator<< (std::basic_ostream<Ch,Traits>& s, const basic_vector2<T>& r)
{
	return s << '(' << r.x << ',' << r.y << ')';
}

template<typename T> inline T length_quad(const basic_vector2<T>& l)
{
	return l.length_quad();
}

template<typename T> inline T length(const basic_vector2<T>& l)
{
	return l.length();
}

typedef basic_vector2<space_unit> point;
typedef basic_vector2<space_unit> vector2;

}

#endif
