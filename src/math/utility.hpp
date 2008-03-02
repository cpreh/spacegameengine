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


#ifndef SGE_UTILITY_HPP_INCLUDED
#define SGE_UTILITY_HPP_INCLUDED

#include <cstdlib>
#include <cmath>
#include <limits>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include "dim.hpp"

namespace sge
{
namespace math
{

template<typename T>
inline T abs(const T &t) 
{ 
	return t >= T(0) ? t : -t; 
}

template<typename T>
inline typename boost::is_unsigned<T>::type unsigned_diff(const T a, const T b)
{
	return a > b ? a - b : b - a;
}

template<typename T>
inline T random(const T &begin,const T &end)
{
	return begin + static_cast<T>(std::rand() / (RAND_MAX + 1.0) * (end - begin));
}

template<typename T>
inline bool nearly_equals(const T& a, const T& b)
{
	return abs(a - b) < std::numeric_limits<T>::epsilon();
}

template<typename T>
inline typename boost::disable_if<boost::is_floating_point<T>, bool>::type compare(const T& a, const T& b)
{
	return a == b;
}

template<typename T>
inline typename boost::enable_if<boost::is_floating_point<T>, bool>::type compare(const T& a, const T& b)
{
	return nearly_equals(a, b);
}

template<typename T>
inline bool almost_zero(const T t)
{
	return compare(t, static_cast<T>(0));
}

inline unsigned log2(const unsigned x)
{
	unsigned r = 0;
	while((x >> r) != 0)
		r++;
	return --r;
}

inline bool is_int_log2(const unsigned x)
{
	return !(x & (x-1));
}

template<typename Base, typename Exp> Base pow_int(const Base base, const Exp e)
{
	if(e == 0)
		return 1;
	Base ret = base;
	for(Exp i = 1; i < e; ++i)
		ret*=base;
	return ret;
}

template<typename T>
typename boost::enable_if<boost::is_integral<T>, T>::type round_div_int(const T  l, const T r)
{
	return (r % 2)
		? ((l * 2 / r) + 1) / 2 // for odd numbers up to half the types capacity
		: (l + (r / 2)) / r;    // for even numbers at least up to half till up
		                        // to 100% of the types capacity, depending on r
		                        // greater r -> less max l
}

template<bool is_integral> struct next_pow_2_implementation {
	template<typename T> static T next_pow_2(const T t)
	{
		return static_cast<T>(std::pow(static_cast<T>(2),std::ceil(std::log(static_cast<double>(t))/std::log(static_cast<double>(2)))));
	}
};

template<> struct next_pow_2_implementation<true> {
	template<typename T> static T next_pow_2(const T t)
	{
		if (t <= 0) std::log(static_cast<double>(-1)); // throw same exception as general template
		if (t & (t-1)) {
			register T c = t & 0x3f,
			           t_copy = t, ret=2;
			while (t_copy >>= 6) { ret <<= 6; c = t_copy & 0x3f; }
			return ret <<= (c & 0x20) ? 5 : (c & 0x10) ? 4 : (c & 0x08) ? 3 : (c & 0x04) ? 2 : (c & 0x02) ? 1 : 0;
		} else return t;
	}
};

template<typename T> inline T next_pow_2(const T t) {
	typedef typename boost::is_integral<T> is_int;
	return next_pow_2_implementation<is_int::value>::next_pow_2(t);
}

template<typename T> inline basic_dim<T, 2> next_pow_2(const basic_dim<T, 2>& r)
{
	return basic_dim<T, 2>(next_pow_2(r.w()), next_pow_2(r.h()));
}

template<typename T>
T clamp(const T& value, const T& vmin, const T& vmax)
{
	return std::max(std::min(value, vmax), vmin);
}

}
}

#endif
