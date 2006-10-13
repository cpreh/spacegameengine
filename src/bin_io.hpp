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


#ifndef SGE_BIN_IO_HPP_INCLUDED
#define SGE_BIN_IO_HPP_INCLUDED

#include <ostream>
#include <istream>
#include <string>

namespace sge
{

template<typename T, typename Ch, class Traits> std::basic_ostream<Ch>& bin_write(std::basic_ostream<Ch,Traits>& s, const T& t)
{
	return s.write(reinterpret_cast<const Ch*>(&t),sizeof(T) / sizeof(Ch));
}

template<typename T, typename Ch, typename Traits> std::basic_istream<Ch>& bin_read(std::basic_istream<Ch,Traits>& s, T& t)
{
	return s.read(reinterpret_cast<Ch*>(&t),sizeof(T) / sizeof(Ch));
}

template<typename Ch, typename Traits> std::basic_ostream<Ch,Traits>& bin_write(std::basic_ostream<Ch,Traits>& s, const std::basic_string<Ch,Traits>& t)
{
	bin_write(s,t.size());
	for(typename std::basic_string<Ch,Traits>::const_iterator it = t.begin(); it != t.end(); ++it)
		bin_write(s,*it);
	return s;
}

template<typename Ch, typename Traits> std::basic_istream<Ch>& bin_read(std::basic_istream<Ch,Traits>& s, std::basic_string<Ch,Traits>& t)
{
	typedef typename std::basic_string<Ch> string_type;
	typename string_type::size_type sz;
	bin_read(s,sz);
	t.resize(sz);
	for(typename string_type::iterator it = t.begin(); it != t.end(); ++it)
		bin_read(s,*it);
	return s;
}

}

#endif
