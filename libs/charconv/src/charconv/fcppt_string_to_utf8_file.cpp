//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/fcppt_string_to_utf8_file.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <ios>
#include <fcppt/config/external_end.hpp>


bool
sge::charconv::fcppt_string_to_utf8_file(
	fcppt::string const &_string,
	std::filesystem::path const &_path
)
{
	std::ofstream file(
		_path
	);

	if(
		!file.is_open()
	)
		return
			false;

	sge::charconv::utf8_string const result(
		sge::charconv::fcppt_string_to_utf8(
			_string
		)
	);

	return
		!file.write(
			fcppt::cast::to_char_ptr<
				char const *
			>(
				result.c_str()
			),
			fcppt::cast::size<
				std::streamsize
			>(
				fcppt::cast::to_signed(
					result.size()
				)
			)
		).fail();
}
