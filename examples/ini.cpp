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


#include <sge/parse/ini/parse_string.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/output/to_stream.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <string>
#include <fcppt/config/external_end.hpp>


int
main()
{
	return
		fcppt::either::match(
			sge::parse::ini::parse_string(
				std::string{
					"[blabla]\nfoo = 42\nconfuse=5\nbar=3.4\nimagepath=/tmp/test\n"
					"[section2]\nblubb=bar\n"
				}
			),
			[](
				fcppt::parse::error<
					char
				> const &_error
			)
			{
				fcppt::io::cerr()
					<<
					fcppt::from_std_string(
						_error.get()
					)
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_FAILURE;
			},
			[](
				sge::parse::ini::start const &_result
			)
			{
				if(
					fcppt::not_(
						sge::parse::ini::output::to_stream(
							fcppt::io::cout(),
							_result
						)
					)
				)
				{
					fcppt::io::cerr()
						<< FCPPT_TEXT("Output failed\n");

					return
						EXIT_FAILURE;
				}

				return
					EXIT_SUCCESS;
			}
		);
}
