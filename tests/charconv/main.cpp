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


#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/encoding_to_string.hpp>
#include <sge/tests/charconv/test_data.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/tag_value.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/mpl/enum_range.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	charconv_main
)
{
FCPPT_PP_POP_WARNING

	boost::filesystem::path const test_data_path(
		boost::filesystem::path(
			SGE_TESTS_CHARCONV_TEST_DATA
		)
		/ "test_data.txt"
	);

	boost::filesystem::ifstream stream(
		test_data_path
	);

	BOOST_REQUIRE(
		stream.is_open()
	);

	std::stringstream stringstream;

	stringstream << stream.rdbuf();

	std::string const input(
		stringstream.str()
	);

	fcppt::algorithm::loop(
		fcppt::mpl::enum_range<
			sge::charconv::encoding
		>::type{},
		[
			&input
		](
			auto const _dest_encoding
		)
		{
			try
			{
				auto const result(
					sge::charconv::convert<
						fcppt::tag_value(
							_dest_encoding
						),
						sge::charconv::encoding::utf8
					>(
						input
					)
				);

				std::string const back(
					sge::charconv::convert<
						sge::charconv::encoding::utf8,
						fcppt::tag_value(
							_dest_encoding
						)
					>(
						result
					)
				);

				fcppt::io::cout()
					<<
					FCPPT_TEXT("Converting to ")
					<<
					sge::charconv::encoding_to_string(
						fcppt::tag_value(
							_dest_encoding
						)
					)
					<<
					FCPPT_TEXT('\n');

				BOOST_CHECK_EQUAL(
					input,
					back
				);
			}
			catch(
				fcppt::exception const &_error
			)
			{
				fcppt::io::cerr()
					<< _error.string()
					<< FCPPT_TEXT('\n');

				BOOST_CHECK(
					false
				);
			}
		}
	);
}
