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


#ifndef SGE_ENDIANNESS_HPP_INCLUDED
#define SGE_ENDIANNESS_HPP_INCLUDED

#include <cstddef>
#include <sge/export.hpp>

#if defined(SGE_LITTLE_ENDIAN) && defined(SGE_BIG_ENDIAN)
#error "SGE_LITTLE_ENDIAN and SGE_BIG_ENDIAN defined!"
#endif

namespace sge
{

SGE_SYMBOL void swap_endianness(unsigned char*, std::size_t len);

SGE_SYMBOL void from_to_big_endianness(unsigned char*, std::size_t len);

SGE_SYMBOL void from_to_little_endianness(unsigned char*, std::size_t len);

template<typename T>
T swap_endianness(T t)
{
	swap_endianness(reinterpret_cast<unsigned char*>(&t), sizeof(T));
	return t;
}

inline bool is_little_endian()
{
#if   defined(SGE_LITTLE_ENDIAN)
	return true;
#elif defined(SGE_BIG_ENDIAN)
	return false;
#else
	typedef int type;
	union {
		type t;
		char c[sizeof(type)];
	} u;
	u.t = 1;

	return u.c[0] == u.t;
#endif
}

template<typename T>
inline T from_to_big_endianness(const T& t)
{
	if(is_little_endian())
		return swap_endianness(t);
	return t;
}

template<typename T>
inline T from_to_little_endianness(const T& t)
{
	if(!is_little_endian())
		return swap_endianness(t);
	return t;
}

}

#endif
