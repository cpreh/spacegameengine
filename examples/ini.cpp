/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/parse/error_string.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <sge/parse/ini/parse_range.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/output/to_stream.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


int
main()
{
	fcppt::string const test(
		FCPPT_TEXT("[blabla]\nfoo = 42\nconfuse=5\nbar=3.4\nimagepath=/tmp/test\n")
		FCPPT_TEXT("[section2]\nblubb=bar\n")
	);

	fcppt::string::const_iterator beg(
		test.begin()
	);

	sge::parse::ini::start result;

	sge::parse::result const ret(
		sge::parse::ini::parse_range(
			beg,
			test.end(),
			result
		)
	);

	if(
		ret.result_code()
		!=
		sge::parse::result_code::ok
	)
	{
		fcppt::maybe_void(
			ret.error_string(),
			[](
				sge::parse::error_string const &_error
			)
			{
				fcppt::io::cerr()
					<< _error
					<< FCPPT_TEXT('\n');
			}
		);

		return
			EXIT_FAILURE;
	}

	if(
		!sge::parse::ini::output::to_stream(
			fcppt::io::cout(),
			result
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
