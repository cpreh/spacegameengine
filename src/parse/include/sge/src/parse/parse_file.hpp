/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_PARSE_PARSE_FILE_HPP_INCLUDED
#define SGE_SRC_PARSE_PARSE_FILE_HPP_INCLUDED

#include <sge/parse/error_string.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{

template<
	typename Result
>
sge::parse::result const
parse_file(
	boost::filesystem::path const &_path,
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

	if(
		!ifs.is_open()
	)
		return
			sge::parse::result(
				sge::parse::result_code::not_open,
				sge::parse::optional_error_string(
					sge::parse::error_string(
						FCPPT_TEXT("Failed to open ")
						+
						fcppt::filesystem::path_to_string(
							_path
						)
					)
				)
			);

	bool const result(
		// use ADL
		parse_stream(
			ifs,
			_result
		)
	);

	if(
		result
	)
		return
			sge::parse::result(
				sge::parse::result_code::ok,
				sge::parse::optional_error_string()
			);

	return
		sge::parse::result(
			ifs.eof()
			?
				sge::parse::result_code::failure
			:
				sge::parse::result_code::partial
			,
			sge::parse::optional_error_string(
				sge::parse::error_string(
					FCPPT_TEXT("Failed to parse ")
					+
					fcppt::filesystem::path_to_string(
						_path
					)
				)
				// TODO: Add error information here!
			)
		);
}

}
}

#endif
