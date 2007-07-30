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


#ifndef SGE_MATH_HPP_INCLUDED
#define SGE_MATH_HPP_INCLUDED

#include <cmath>
#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{

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
		: (l + (r / 2)) / r;   // for even numbers at least up to half till up
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
			register unsigned char c = t & 0x3f;
			register T t_copy = t, ret=2;
			while (t_copy >>= 6) { ret <<= 6; c = t_copy & 0x3f; }
			return ret <<= (c & 0x20) ? 5 : (c & 0x10) ? 4 : (c & 0x08) ? 3 : (c & 0x04) ? 2 : (c & 0x02) ? 1 : 0;
		} else return t;
	}
};

template<typename T> inline T next_pow_2(const T t) {
	typedef typename boost::is_integral<T> is_int;
	return next_pow_2_implementation<is_int::value>::next_pow_2(t);
}

}

#endif
