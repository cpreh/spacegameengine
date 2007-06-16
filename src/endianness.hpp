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


#ifndef SGE_ENDIANNESS_HPP_INCLUDED
#define SGE_ENDIANNESS_HPP_INCLUDED

#include <algorithm>

namespace sge
{

template<typename T>
T swap_endianness(const T& t)
{
	T dest;
	typedef unsigned char temp_type;
	std::reverse_copy(reinterpret_cast<const temp_type*>(&t), reinterpret_cast<const temp_type*>(&t) + sizeof(T), reinterpret_cast<temp_type*>(&dest));
	return dest;
}

bool is_little_endian()
{
	typedef int type;
	union {
		type t;
		char c[sizeof(type)];
	} u;
	u.t = 1;

	return u.c[0] == u.t;
}

template<typename T>
T from_big_endianness(const T& t)
{
	if(is_little_endian())
		return swap_endianness(t);
	return t;
}

template<typename T>
T to_big_endianness(const T& t)
{
	return from_big_endianness(t);
}

}

#endif
