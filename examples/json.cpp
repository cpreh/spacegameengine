/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/parse/json/parse_stream.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <cstdlib>

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

	fcppt::string::const_iterator beg(
		test.begin()
	);

	sge::parse::json::object result;

	if(
		!sge::parse::json::parse_stream(
			ss,
			result
		)
	)
	{
		fcppt::io::cerr
			<< FCPPT_TEXT("failure\n");

		return EXIT_FAILURE;
	}

	// assert that we have member foo
	sge::parse::json::find_member_exn<
		int
	>(
		result.members,
		FCPPT_TEXT("foo")
	);

	if(
		!sge::parse::json::output::to_stream(
			fcppt::io::cout,
			result
		)
	)
	{
		fcppt::io::cerr
			<< FCPPT_TEXT("output failed\n");

		return EXIT_FAILURE;
	}

	fcppt::io::cout
		<< FCPPT_TEXT('\n');
}
catch(
	fcppt::exception const &e
)
{
	fcppt::io::cerr
		<< FCPPT_TEXT("caugth exception: ")
		<< e.string()
		<< FCPPT_TEXT('\n');
	
	return EXIT_FAILURE;
}
