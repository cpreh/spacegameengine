/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_PARSE_STREAM_HPP_INCLUDED
#define SGE_PARSE_PARSE_STREAM_HPP_INCLUDED

#include <fcppt/io/istream.hpp>
#include <fcppt/char_type.hpp>
#include <boost/spirit/home/support/iterators/istream_iterator.hpp>

namespace sge
{
namespace parse
{

template<
	typename Result
>
bool
parse_stream(
	fcppt::io::istream &ifs,
	Result &result
)
{
	typedef boost::spirit::basic_istream_iterator<
		fcppt::char_type
	> istream_iterator;

	istream_iterator begin(
		ifs
	);

	return
		parse_range(
			begin,
			istream_iterator(),
			result
		);
}

}
}

#endif
