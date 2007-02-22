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

// FIXME: may overflow too easily
template<typename T> T round_div_int(const T  l, const T r)
{
	return ((l * 10 / r) + 5) / 10;
}

template<typename T> T next_pow_2(const T t)
{
	return static_cast<T>(std::pow(2.0,std::ceil(std::log(static_cast<double>(t))/std::log(2.0))));
}

}

#endif
