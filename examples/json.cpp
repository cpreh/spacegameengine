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


#include <sge/parse/make_error_string.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_stream.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int main()
try
{
	fcppt::string const test(
		FCPPT_TEXT("{ \"foo\": 42, \"bar\" : { \"inner\" : 5.5, \"booltest\" : true } }")
	);

	fcppt::io::istringstream
		ss(
			test
		);

	sge::parse::json::start result;

	sge::parse::result const ret(
		sge::parse::json::parse_stream(
			ss,
			result
		)
	);

	if(
		ret.result_code()
		!=
		sge::parse::result_code::ok
	)
	{
		fcppt::io::cerr()
			<< sge::parse::make_error_string(
				ret
			)
			<< FCPPT_TEXT('\n');

		return EXIT_FAILURE;
	}

	// assert that we have member foo
	sge::parse::json::find_member_exn<
		sge::parse::json::int_type
	>(
		result.object().members,
		FCPPT_TEXT("foo")
	);

	// test if this also works with const results
	{
		sge::parse::json::object const &const_result(
			result.object()
		);

		sge::parse::json::find_member_exn<
			sge::parse::json::int_type
		>(
			const_result.members,
			FCPPT_TEXT("foo")
		);
	}

	if(
		!sge::parse::json::output::to_stream(
			fcppt::io::cout(),
			result
		)
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("output failed\n");

		return EXIT_FAILURE;
	}

	fcppt::io::cout()
		<< FCPPT_TEXT('\n');
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< FCPPT_TEXT("caugth exception: ")
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cout
		<< "caught exception: "
		<< _exception.what()
		<< '\n';

	return EXIT_FAILURE;
}
