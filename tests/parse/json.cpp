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


#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_stream.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

bool
print_exception(
	fcppt::exception const &_exception
)
{
	fcppt::io::cout()
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return true;
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	parse_json_object
)
{
FCPPT_PP_POP_WARNING

	fcppt::string const test(
		FCPPT_TEXT("{")
			FCPPT_TEXT("\"foo\": 42,")
			FCPPT_TEXT("\"bar\" :")
			FCPPT_TEXT("{")
				FCPPT_TEXT("\"inner\" : 5.5,")
				FCPPT_TEXT("\"booltest\" : true")
			FCPPT_TEXT("}")
		FCPPT_TEXT("}")
	);

	fcppt::io::istringstream ss(
		test
	);

	sge::parse::json::start result;

	BOOST_REQUIRE(
		sge::parse::json::parse_stream(
			ss,
			result
		).result_code()
		==
		sge::parse::result_code::ok
	);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	parse_json_array
)
{
FCPPT_PP_POP_WARNING

	fcppt::string const test(
		FCPPT_TEXT("[")
			FCPPT_TEXT("42,")
			FCPPT_TEXT("100")
		FCPPT_TEXT("]")
	);

	fcppt::io::istringstream ss(
		test
	);

	sge::parse::json::start result;

	BOOST_REQUIRE(
		sge::parse::json::parse_stream(
			ss,
			result
		).result_code()
		==
		sge::parse::result_code::ok
	);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	parse_json_error
)
{
FCPPT_PP_POP_WARNING

	fcppt::string const test(
		FCPPT_TEXT("{")
			FCPPT_TEXT("\"foo\": 42,")
			FCPPT_TEXT("\"bar\" :")
			FCPPT_TEXT("{")
				FCPPT_TEXT("\"inner\" : 5.5,")
				FCPPT_TEXT("\"booltest\" : true")
			FCPPT_TEXT("}")
		FCPPT_TEXT("")
	);

	fcppt::io::istringstream ss(
		test
	);

	sge::parse::json::start result;

	BOOST_REQUIRE_EXCEPTION(
		sge::parse::json::parse_stream(
			ss,
			result
		),
		fcppt::exception,
		::print_exception
	);
}
