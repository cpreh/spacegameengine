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


#ifndef SGE_SRC_PARSE_OUTPUT_TO_STREAM_HPP_INCLUDED
#define SGE_SRC_PARSE_OUTPUT_TO_STREAM_HPP_INCLUDED

#include <fcppt/io/ostream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace output
{

template<
	typename Data
>
bool
to_stream(
	fcppt::io::ostream &ofs,
	Data const &data
)
{
	typedef std::ostream_iterator<
		fcppt::io::ostream::char_type,
		fcppt::io::ostream::char_type
	> ostream_iterator;

	ostream_iterator sink(
		ofs
	);

	return
		SGE_PARSE_DETAIL_TO_RANGE_NAMESPACE :: to_range(
			sink,
			data
		);
#undef SGE_PARSE_DETAIL_TO_RANGE_NAMESPACE
}

}
}
}

#endif
