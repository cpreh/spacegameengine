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


#ifndef SGE_BIT_HPP_INCLUDED
#define SGE_BIT_HPP_INCLUDED

#include <cstddef>
#include <climits>
#include <boost/array.hpp>

namespace sge
{

inline bool bit(const char c, const unsigned bit)
{
	return c & (1<<bit);
}
inline bool bit_a(const char c[], const unsigned bit)
{
	return c[bit/CHAR_BIT]&(1<<(bit%CHAR_BIT));
}
template<std::size_t sz> inline bool bit_a(const boost::array<char,sz>& c, const unsigned bit)
{
	return bit_a(c.data(),bit);
}

}

#endif
