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


#include <sge/charconv/const_raw_pointer.hpp>
#include <sge/charconv/convert_raw.hpp>
#include <sge/charconv/create_system.hpp>
#include <sge/charconv/dest_encoding.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/encoding_to_string.hpp>
#include <sge/charconv/raw_vector.hpp>
#include <sge/charconv/source_encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/system.hpp>
#include <sge/charconv/system_scoped_ptr.hpp>
#include <sge/charconv/unsupported_conversion.hpp>
#include <sge/tests/charconv/test_data.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/data.hpp>
#include <fcppt/container/data_end.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

void
test_convert_from_to(
	sge::charconv::system &_system,
	sge::charconv::source_encoding const _source,
	sge::charconv::dest_encoding const _dest,
	sge::charconv::input_range const &_raw_data
)
{
	sge::charconv::raw_vector const result(
		sge::charconv::convert_raw(
			_system,
			_source,
			_dest,
			_raw_data
		)
	);

	sge::charconv::raw_vector const result2(
		sge::charconv::convert_raw(
			_system,
			sge::charconv::source_encoding(
				_dest.get()
			),
			sge::charconv::dest_encoding(
				_source.get()
			),
			sge::charconv::input_range(
				result.begin(),
				result.end()
			)
		)
	);

	BOOST_REQUIRE(
		result2.size()
		==
		static_cast<
			sge::charconv::raw_vector::size_type
		>(
			_raw_data.size()
		)
	);

	BOOST_REQUIRE((
		std::equal(
			_raw_data.begin(),
			_raw_data.end(),
			result2.begin()
		)
	));
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	charconv_main
)
{
FCPPT_PP_POP_WARNING

	sge::charconv::system_scoped_ptr const system(
		sge::charconv::create_system()
	);

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

	std::string const data(
		stringstream.str()
	);

	sge::charconv::input_range const input(
		reinterpret_cast<
			sge::charconv::const_raw_pointer
		>(
			fcppt::container::data(
				data
			)
		),
		reinterpret_cast<
			sge::charconv::const_raw_pointer
		>(
			fcppt::container::data_end(
				data
			)
		)
	);

	FCPPT_FOREACH_ENUMERATOR(
		dest_encoding,
		sge::charconv::encoding
	)
	try
	{
		test_convert_from_to(
			*system,
			sge::charconv::source_encoding(
				sge::charconv::encoding::utf8
			),
			sge::charconv::dest_encoding(
				dest_encoding
				),
			input
		);
	}
	catch(
		sge::charconv::unsupported_conversion const &_error
	)
	{
		fcppt::io::cerr()
			<<
			FCPPT_TEXT("Unsupported conversion from ")
			<<
			sge::charconv::encoding_to_string(
				_error.source().get()
			)
			<<
			FCPPT_TEXT(" to ")
			<<
			sge::charconv::encoding_to_string(
				_error.dest().get()
			)
			<<
			FCPPT_TEXT('\n');
	}
	catch(
		fcppt::exception const &_error
	)
	{
		fcppt::io::cerr()
			<< _error.string()
			<< FCPPT_TEXT('\n');

		BOOST_CHECK(false);
	}
}
