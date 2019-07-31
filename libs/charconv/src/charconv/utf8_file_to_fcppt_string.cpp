//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/utf8_file_to_fcppt_string.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


fcppt::optional_string
sge::charconv::utf8_file_to_fcppt_string(
	boost::filesystem::path const &_path
)
{
	boost::filesystem::ifstream file_stream(
		_path
	);

	if(
		!file_stream.is_open()
	)
		return
			fcppt::optional_string();

	typedef std::istreambuf_iterator<
		char
	> iterator;

	return
		fcppt::optional_string(
			sge::charconv::utf8_string_to_fcppt(
				sge::charconv::utf8_string(
					iterator(
						file_stream
					),
					iterator()
				)
			)
		);
}
