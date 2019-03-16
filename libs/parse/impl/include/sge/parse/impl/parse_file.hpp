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

#include <sge/parse/file_result.hpp>
#include <fcppt/string_literal.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/parse/grammar_fwd.hpp>
#include <fcppt/parse/grammar_parse_stream.hpp>
#include <fcppt/parse/result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fstream>
#include <ios>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace impl
{

template<
	typename Result,
	typename Ch,
	typename Skipper
>
sge::parse::file_result<
	Ch,
	Result
>
parse_file(
	boost::filesystem::path const &_path,
	fcppt::parse::grammar<
		Result,
		Ch,
		Skipper
	> const &_grammar
)
{
	return
		fcppt::optional::maybe(
			fcppt::filesystem::open<
				std::basic_ifstream<
					Ch
				>
			>(
				_path,
				std::ios_base::binary
			),
			[]{
				return
					fcppt::either::make_failure<
						Result
					>(
						fcppt::optional::object<
							fcppt::parse::error<
								Ch
							>
						>{}
					);
			},
			[
				&_grammar,
				&_path
			](
				std::basic_istream<
					Ch
				> &&_ifs
			)
			{
				_ifs.unsetf(
					std::ios_base::skipws
				);

				return
					fcppt::either::map_failure(
						fcppt::parse::grammar_parse_stream(
							_ifs,
							_grammar
						),
						[
							&_path
						](
							fcppt::parse::error<
								Ch
							> &&_failure
						)
						{
							return
								fcppt::optional::make(
									fcppt::parse::error<
										Ch
									>{
										FCPPT_STRING_LITERAL(
											Ch,
											"Failed to parse \""
										)
										+
										_path.string<
											std::basic_string<
												Ch
											>
										>()
										+
										FCPPT_STRING_LITERAL(
											Ch,
											"\": "
										)
										+
										std::move(
											_failure.get()
										)
									}
								);
						}
					);
			}
		);
}

}
}
}

#endif
