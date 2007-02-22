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


#ifndef SGE_STRING_HPP_INCLUDED
#define SGE_STRING_HPP_INCLUDED

#include "typeswitch.hpp"
#include "ucs4.hpp"
#include <string>

namespace sge
{

typedef std::basic_string<uchar_t> ustring;

class string : public ustring {
public:
	string(const std::string& s, std::string::size_type pos = 0, std::string::size_type n = npos, const allocator_type& alloc = allocator_type());
	string(std::string::const_pointer p, std::string::size_type n, const allocator_type& alloc = allocator_type());
	string(std::string::const_pointer p, const allocator_type& alloc = allocator_type());
	string(std::string::size_type n, std::string::value_type c, const allocator_type& alloc = allocator_type());
/*	template<typename In>
		string(In beg, In end, const allocator_type& alloc = allocator_type())
	{
	}*/
	
	explicit string(const allocator_type& alloc = allocator_type());
	string(const string& s, size_type pos = 0, size_type n = npos, const allocator_type& alloc = allocator_type());
	string(const_pointer p, size_type n, const allocator_type& alloc = allocator_type());
	string(const_pointer p, const allocator_type& alloc = allocator_type());
	string(size_type n, value_type c, const allocator_type& alloc = allocator_type());

	string(const ustring& s)
	 : ustring(s) {}

	string substr(size_type first, size_type count = npos)
	{
		return string(ustring::substr(first,count));
	}
};

}

#endif
