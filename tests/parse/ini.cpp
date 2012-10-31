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
#include <sge/parse/ini/parse_stream.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/output/to_stream.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <boost/test/unit_test.hpp>
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

	BOOST_CHECK((
		sge::parse::ini::parse_stream(
			stream,
			result
		).result_code()
		!=
		sge::parse::result_code::ok
	));

	sge::parse::ini::output::to_stream(
		fcppt::io::cout(),
		result
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	parse_ini
)
{
FCPPT_PP_POP_WARNING

	fcppt::string const test(
		FCPPT_TEXT("[section]\n")
			FCPPT_TEXT("foo1 = bar1\n")
		FCPPT_TEXT("[sectionfoo]\n")
			FCPPT_TEXT("foo3 =	 bar3\n")
			FCPPT_TEXT("foo4=bar4\n")
	);

	fcppt::io::istringstream stream(
		test
	);

	stream.unsetf(
		std::ios_base::skipws
	);

	sge::parse::ini::start result;

	BOOST_REQUIRE(
		sge::parse::ini::parse_stream(
			stream,
			result
		).result_code()
		==
		sge::parse::result_code::ok
	);

	sge::parse::ini::output::to_stream(
		fcppt::io::cout(),
		result
	);

	fcppt::io::cout()
		<< FCPPT_TEXT('\n');

	BOOST_REQUIRE(
		stream.eof()
	);

	BOOST_REQUIRE(
		result.sections.size() == 2u
	);

	BOOST_REQUIRE(
		result.sections[0].entries.size() == 1u
	);

	BOOST_REQUIRE(
		result.sections[1].entries.size() == 2u
	);

	BOOST_CHECK(
		result.sections[0].entries[0].name == FCPPT_TEXT("foo1")
		&&
		result.sections[0].entries[0].value == FCPPT_TEXT("bar1")
	);

	BOOST_CHECK(
		result.sections[1].entries[0].name == FCPPT_TEXT("foo3")
		&&
		result.sections[1].entries[0].value == FCPPT_TEXT("bar3")
	);

	BOOST_CHECK(
		result.sections[1].entries[1].name == FCPPT_TEXT("foo4")
		&&
		result.sections[1].entries[1].value == FCPPT_TEXT("bar4")
	);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	parse_ini_error
)
{
FCPPT_PP_POP_WARNING

	check_failure(
		FCPPT_TEXT("garbage")
	);

	check_failure(
		FCPPT_TEXT("[foo]")
		FCPPT_TEXT("missing_newline")
	);
}
