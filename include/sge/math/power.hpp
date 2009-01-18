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


#ifndef SGE_MATH_POWER_HPP_INCLUDED
#define SGE_MATH_POWER_HPP_INCLUDED

#include <cmath>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include "dim/static.hpp"
#include "dim/basic_decl.hpp"

namespace sge
{
namespace math
{

/**
 * Calculates \f$\textrm{base}^e\f$ using integer arithmetics (no cast to float
 * and std::pow needed)
 */
template<typename Base, typename Exp> Base pow_int(const Base base, const Exp e)
{
	if(e == 0)
		return 1;
	Base ret = base;
	for(Exp i = 1; i < e; ++i)
		ret*=base;
	return ret;
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

/**
 * "Rounds up" \c t to the next power of 2
 */
template<typename T> inline T next_pow_2(const T t) {
	typedef typename boost::is_integral<T> is_int;
	return next_pow_2_implementation<is_int::value>::next_pow_2(t);
}

/**
 * "Rounds up" both components of \c r to the next power of two
 */
template<typename T>
typename dim::static_<T, 2>::type const
next_pow_2(
	typename dim::static_<T, 2>::type const &r)
{
	return typename dim::static_<T, 2>::type(
		next_pow_2(r.w()),
		next_pow_2(r.h()));
}

/**
 * Checks if an unsigned type is a power of two
 */
template<typename T>
inline typename boost::enable_if<
	boost::is_unsigned<T>,
	bool
>::type
is_power_of_2(
	T const t)
{
	return t && !(t & (t - 1));
}

template<typename T>
typename boost::enable_if<
	boost::is_unsigned<T>,
	bool
>::type
is_power_of_2(
	typename dim::static_<T, 2>::type const &d)
{
	return is_power_of_2(d.w()) && is_power_of_2(d.h());
}

/**
 * Returns the square of \c (this is pretty dumb)
 */
template<typename T>
inline T quad(T const& t)
{
	return t*t;
}

}
}

#endif
