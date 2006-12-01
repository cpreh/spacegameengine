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


#ifndef SGE_DIM_HPP_INCLUDED
#define SGE_DIM_HPP_INCLUDED

#include "../types.hpp"
#include "./vector2.hpp"

namespace sge
{

template<typename T>
struct basic_dim {
	typedef T value_type;
	basic_dim(const value_type& w = value_type(), const value_type& h = value_type())
		: w(w), h(h) {}
	explicit basic_dim(const math::vector<T,2>& v)
		: w(v.x), h(v.y) {}
	value_type w,h;
};

template<typename T> basic_dim<T> operator+(const basic_dim<T>& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l.w + r.w, l.h + r.h);
}

template<typename T> basic_dim<T> operator-(const basic_dim<T>& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l.w - r.w, l.h - r.h);
}

template<typename T> basic_dim<T> operator*(const basic_dim<T>& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l.w * r.w, l.h * r.h);
}

template<typename T> basic_dim<T> operator/(const basic_dim<T>& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l.w / r.w, l.h / r.h);
}

template<typename T> basic_dim<T> operator+(const T& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l + r.w, l + r.h);
}

template<typename T> basic_dim<T> operator-(const T& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l - r.w, l - r.h);
}

template<typename T> basic_dim<T> operator*(const T& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l * r.w, l * r.h);
}

template<typename T> basic_dim<T> operator/(const basic_dim<T>& l, const T& r)
{
	return basic_dim<T>(l.w / r, l.h / r);
}

template<typename T, typename Ch, typename Traits> std::basic_ostream<Ch,Traits>& operator<< (std::basic_ostream<Ch,Traits>& os, const basic_dim<T>& d)
{
	return os << '(' << d.w << ',' << d.h << ')';
}

typedef basic_dim<space_unit> dim;

}

#endif

