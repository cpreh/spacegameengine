//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/exception.hpp>
#include <sge/charconv/utf8_file_to_fcppt_string.hpp>
#include <sge/charconv/utf8_file_to_fcppt_string_exn.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


fcppt::string
sge::charconv::utf8_file_to_fcppt_string_exn(
	boost::filesystem::path const &_path
)
{
	return
		fcppt::optional::to_exception(
			sge::charconv::utf8_file_to_fcppt_string(
				_path
			),
			[
				&_path
			]{
				return
					sge::charconv::exception(
						FCPPT_TEXT("Couldn't open file ")
						+
						fcppt::filesystem::path_to_string(
							_path
						)
					);
			}
		);
}
