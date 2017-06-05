/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PARSE_IMPL_PARSE_FILE_HPP_INCLUDED
#define SGE_PARSE_IMPL_PARSE_FILE_HPP_INCLUDED

#include <sge/parse/error_string.hpp>
#include <sge/parse/make_error_string.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/ifstream.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace impl
{

template<
	typename Result
>
sge::parse::result
parse_file(
	boost::filesystem::path const &_path,
	Result &_result
)
{
	return
		fcppt::optional::maybe(
			fcppt::filesystem::open<
				fcppt::filesystem::ifstream
			>(
				_path,
				std::ios_base::binary
			),
			[
				&_path
			]{
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
			},
			[
				&_result,
				&_path
			](
				fcppt::filesystem::ifstream &&_ifs
			)
			{
				_ifs.unsetf(
					std::ios_base::skipws
				);

				sge::parse::result const result(
					// use ADL
					parse_stream(
						_ifs,
						_result
					)
				);

				return
					result.result_code()
					==
					sge::parse::result_code::ok
					?
						result
					:
						sge::parse::result(
							result.result_code(),
							sge::parse::optional_error_string(
								sge::parse::error_string(
									FCPPT_TEXT("Failed to parse \"")
									+
									fcppt::filesystem::path_to_string(
										_path
									)
									+
									FCPPT_TEXT("\", ")
								)
								+
								sge::parse::make_error_string(
									result
								)
							)
						);
			}
		);
}

}
}
}

#endif
