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
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <boost/test/unit_test.hpp>

namespace
{

bool
print_exception(
	fcppt::exception const &_exception
)
{
	fcppt::io::cout
		<< _exception.string()
		<< FCPPT_TEXT('\n');
	
	return true;
}

}

BOOST_AUTO_TEST_CASE(
	parse_json_main
)
{
	fcppt::string const test(
		FCPPT_TEXT(
			"{"
				"\"foo\": 42,"
				"\"bar\" :"
				"{"
					"\"inner\" : 5.5,"
					"\"booltest\" : true"
				"}"
			"}"
		)
	);

	fcppt::io::istringstream ss(
		test
	);

	sge::parse::json::object result;

	BOOST_REQUIRE(
		sge::parse::json::parse_stream(
			ss,
			result
		)
	);
}

BOOST_AUTO_TEST_CASE(
	parse_json_error
)
{
	fcppt::string const test(
		FCPPT_TEXT(
			"{"
				"\"foo\": 42,"
				"\"bar\" :"
				"{"
					"\"inner\" : 5.5,"
					"\"booltest\" : true"
				"}"
			""
		)
	);

	fcppt::io::istringstream ss(
		test
	);

	sge::parse::json::object result;

	BOOST_REQUIRE_EXCEPTION(
		sge::parse::json::parse_stream(
			ss,
			result
		),
		fcppt::exception,
		::print_exception
	);
}
