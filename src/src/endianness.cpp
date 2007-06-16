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


#include <algorithm>
#include "../endianness.hpp"

void sge::swap_endianness(unsigned char* const t, std::size_t len)
{
	typedef unsigned char temp_type;
	std::reverse_copy(reinterpret_cast<const temp_type*>(t), reinterpret_cast<const temp_type*>(t) + len, reinterpret_cast<temp_type*>(t));
}

void sge::from_to_big_endianness(unsigned char* const t, std::size_t len)
{
	if(is_little_endian())
		swap_endianness(t, len);
}

void sge::from_to_little_endianness(unsigned char* const t, std::size_t len)
{
	if(!is_little_endian())
		swap_endianness(t, len);
}

