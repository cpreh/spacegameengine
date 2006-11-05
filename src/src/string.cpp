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


#include "../string.hpp"
#include "../iconv.hpp"

sge::string::string(const std::string& s, const std::string::size_type pos, const std::string::size_type n, const allocator_type& alloc)
 : ustring(iconv(s.substr(pos,n)))
{}

sge::string::string(const std::string::const_pointer p, const std::string::size_type n, const allocator_type& alloc)
 : ustring(iconv(std::string(p,n)))
{}

sge::string::string(const std::string::const_pointer p, const allocator_type& alloc)
 : ustring(iconv(std::string(p)))
{}

sge::string::string(const std::string::size_type n, const std::string::value_type c, const allocator_type& alloc)
 : ustring(iconv(std::string(n,c)))
{}


sge::string::string(const allocator_type& alloc)
 : ustring(alloc)
{}

sge::string::string(const string& s, const size_type pos, const size_type n, const allocator_type& alloc)
 : ustring(s,pos,n,alloc)
{}

sge::string::string(const const_pointer p, const size_type n, const allocator_type& alloc)
 : ustring(p,n,alloc)
{}

sge::string::string(const const_pointer p, const allocator_type& alloc)
 : ustring(p,alloc)
{}

sge::string::string(const size_type n, const value_type c, const allocator_type& alloc)
 : ustring(n,c,alloc)
{}

