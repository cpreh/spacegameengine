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


#include "../detail/iconv_detail.hpp"
#undef iconv
#include "../iconv.hpp"

#ifndef SGE_NARROW_STRING
SGE_SYMBOL sge::string sge::iconv(const std::string& input, const encoding from, const string::allocator_type& alloc)
{
	return _iconv<string>(input, from, internal_encoding, alloc);
}

SGE_SYMBOL std::string sge::iconv(const string& input, const encoding to, const std::string::allocator_type& alloc)
{
	return _iconv<std::string>(input, internal_encoding, to, alloc);
}
#else
SGE_SYMBOL sge::string sge::iconv(const string& s)
{
	return s;
}
#endif
