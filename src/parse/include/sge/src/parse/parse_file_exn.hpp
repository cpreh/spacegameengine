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


#ifndef SGE_SRC_PARSE_PARSE_FILE_EXN_HPP_INCLUDED
#define SGE_SRC_PARSE_PARSE_FILE_EXN_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <sge/src/parse/parse_file.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>


namespace sge
{
namespace parse
{

template<
	typename Result
>
Result const
parse_file_exn(
	fcppt::filesystem::path const &_path
)
{
	Result result;

	if(
		!parse::parse_file(
			_path,
			result
		)
	)
		throw sge::parse::exception(
			FCPPT_TEXT("Unable to parse file \"")
			+
			fcppt::filesystem::path_to_string(
				_path
			)
		);

	return result;
}

}
}

#endif
