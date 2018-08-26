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
#include <sge/parse/ini/parse_stream.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/output/to_stream.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


namespace
{

void
check_failure(
	fcppt::string const &_input
)
{
	fcppt::io::istringstream stream(
		_input
	);

	stream.unsetf(
		std::ios_base::skipws
	);

	sge::parse::ini::start result;

	CHECK(
		sge::parse::ini::parse_stream(
			stream,
			result
		).result_code()
		!=
		sge::parse::result_code::ok
	);

	CHECK(
		sge::parse::ini::output::to_stream(
			fcppt::io::cout(),
			result
		)
	);
}

}

TEST_CASE(
	"parse_ini",
	"[sge]"
)
{
	fcppt::string const test(
		FCPPT_TEXT("[section]\n")
			FCPPT_TEXT("foo1 = bar1\n")
		FCPPT_TEXT("[sectionfoo]\n")
			FCPPT_TEXT("foo3 =	 bar3\n")
			FCPPT_TEXT("foo4=bar4\n")
			FCPPT_TEXT("\n")
			FCPPT_TEXT("empty=\n")
	);

	fcppt::io::istringstream stream(
		test
	);

	stream.unsetf(
		std::ios_base::skipws
	);

	sge::parse::ini::start result;

	REQUIRE(
		sge::parse::ini::parse_stream(
			stream,
			result
		).result_code()
		==
		sge::parse::result_code::ok
	);

	REQUIRE(
		sge::parse::ini::output::to_stream(
			fcppt::io::cout(),
			result
		)
	);

	REQUIRE(
		stream.eof()
	);

	// TODO: Improve this
	REQUIRE(
		result.sections.size()
		==
		2u
	);

	REQUIRE(
		result.sections[0].entries.size()
		==
		1u
	);

	REQUIRE(
		result.sections[1].entries.size()
		==
		3u
	);

	CHECK(
		result.sections[0].entries[0].name
		==
		FCPPT_TEXT("foo1")
	);

	CHECK(
		result.sections[0].entries[0].value
		==
		FCPPT_TEXT("bar1")
	);

	CHECK(
		result.sections[1].entries[0].name
		==
		FCPPT_TEXT("foo3")
	);

	CHECK(
		result.sections[1].entries[0].value
		==
		FCPPT_TEXT("bar3")
	);

	CHECK(
		result.sections[1].entries[1].name
		==
		FCPPT_TEXT("foo4")
	);

	CHECK(
		result.sections[1].entries[1].value
		==
		FCPPT_TEXT("bar4")
	);

	CHECK(
		result.sections[1].entries[2].name
		==
		FCPPT_TEXT("empty")
	);

	CHECK(
		result.sections[1].entries[2].value
		==
		FCPPT_TEXT("")
	);
}

TEST_CASE(
	"parse_ini error",
	"[sge]"
)
{
	check_failure(
		FCPPT_TEXT("garbage")
	);

	check_failure(
		FCPPT_TEXT("[foo]")
		FCPPT_TEXT("missing_newline")
	);

	check_failure(
		FCPPT_TEXT("[foo]")
		FCPPT_TEXT("invalid name=foo")
	);
}
