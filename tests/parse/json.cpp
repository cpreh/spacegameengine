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


#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_stream.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch.hpp>
#include <fcppt/config/external_end.hpp>


TEST_CASE(
	"parse_json object",
	"sge]"
)
{
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

	REQUIRE(
		sge::parse::json::parse_stream(
			ss,
			result
		).result_code()
		==
		sge::parse::result_code::ok
	);

	CHECK(
		sge::parse::json::find_member<
			sge::parse::json::int_type
		>(
			result.object().members,
			FCPPT_TEXT("foo")
		).has_value()
	);
}

TEST_CASE(
	"parse_json array",
	"[sge]"
)
{
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

	REQUIRE(
		sge::parse::json::parse_stream(
			ss,
			result
		).result_code()
		==
		sge::parse::result_code::ok
	);
}

TEST_CASE(
	"parse_json error",
	"[sge]"
)
{
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

	sge::parse::result const ret(
		sge::parse::json::parse_stream(
			ss,
			result
		)
	);

	REQUIRE(
		ret.result_code()
		!=
		sge::parse::result_code::ok
	);
}
