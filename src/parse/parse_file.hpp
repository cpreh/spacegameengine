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


#ifndef SGE_PARSE_PARSE_FILE_HPP_INCLUDED
#define SGE_PARSE_PARSE_FILE_HPP_INCLUDED

#include "parse_stream.hpp"
#include <fcppt/filesystem/path.hpp>
#include <fcppt/io/ifstream.hpp>
#include <iosfwd>

namespace sge
{
namespace parse
{

template<
	typename Result
>
bool
parse_file(
	fcppt::filesystem::path const &_path,
	Result &_result
)
{
	fcppt::io::ifstream ifs(
		_path,
		std::ios_base::binary
	);

	ifs.unsetf(
		std::ios_base::skipws
	);

	return 
		ifs.is_open()
		&&
		// use ADL
		parse_stream(
			ifs,
			_result
		)
		&& ifs.eof();
}

}
}

#endif
