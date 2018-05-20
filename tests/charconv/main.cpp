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


#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/tests/charconv/test_data.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_brigand.hpp>
#include <fcppt/brigand/enum_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <catch.hpp>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>


TEST_CASE(
	"charconv",
	"[sge]"
)
{
	boost::filesystem::path const test_data_path(
		boost::filesystem::path(
			SGE_TESTS_CHARCONV_TEST_DATA
		)
		/ "test_data.txt"
	);

	boost::filesystem::ifstream stream(
		test_data_path
	);

	REQUIRE(
		stream.is_open()
	);

	std::stringstream stringstream;

	stringstream << stream.rdbuf();

	std::string const input(
		stringstream.str()
	);

	fcppt::algorithm::loop(
		fcppt::brigand::enum_range<
			sge::charconv::encoding
		>{},
		[
			&input
		](
			auto const _dest_encoding
		)
		{
			FCPPT_USE(
				_dest_encoding
			);

			typedef
			fcppt::tag_type<
				decltype(
					_dest_encoding
				)
			>
			dest_encoding;

			auto const result(
				sge::charconv::convert<
					dest_encoding::value,
					sge::charconv::encoding::utf8
				>(
					input
				)
			);

			std::string const back(
				sge::charconv::convert<
					sge::charconv::encoding::utf8,
					dest_encoding::value
				>(
					result
				)
			);

			CHECK(
				input
				==
				back
			);
		}
	);
}
