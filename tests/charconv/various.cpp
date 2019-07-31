//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <fcppt/config/external_end.hpp>


TEST_CASE(
	"charconv various",
	"[sge]"
)
{
	sge::charconv::utf8_string const empty_result(
		sge::charconv::fcppt_string_to_utf8(
			fcppt::string()
		)
	);

	CHECK(
		empty_result.empty()
	);
}
