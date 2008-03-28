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


#ifndef SGE_ICONV_HPP_INCLUDED
#define SGE_ICONV_HPP_INCLUDED

#include "config.h"
#include "string.hpp"
#include "export.hpp"
#include "iconv_types.hpp"
#include <string>

namespace sge
{

#ifndef SGE_NARROW_STRING
SGE_SYMBOL string  iconv(
	const std::string& input,
	encoding from
		= enc_string_literal,
	const string::allocator_type& alloc
		= string::allocator_type());

SGE_SYMBOL std::string iconv(
	const string& input,
	encoding to
		= enc_string_literal,
	const std::string::allocator_type& alloc
		= std::string::allocator_type());
#else
SGE_SYMBOL string iconv(const string&);
#endif

}

#endif
