/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_DETAIL_PARSE_STREAM_HPP_INCLUDED
#define SGE_PARSE_DETAIL_PARSE_STREAM_HPP_INCLUDED

#include <sge/istream.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace parse
{
namespace detail
{
template<
	typename Result
>
bool
parse_stream(
	istream &ifs,
	Result &result
)
{
	string ret;

	{
		istream::char_type ch;
		while(ifs.get(ch))
			ret.push_back(ch);
	}
	
	typedef string::const_iterator iterator;

	iterator beg(
		ret.begin()
	);

	return parse_range(
		beg,
		static_cast<
			string const &
		>(
			ret
		).end(),
		result
	);
}
}
}
}

#endif
