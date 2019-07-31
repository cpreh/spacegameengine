//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/exception.hpp>
#include <sge/config/impl/try_create_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/error_from_optional.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/filesystem/create_directories_recursive.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/system/error_code_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/system/error_code.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::path
sge::config::impl::try_create_path(
	boost::filesystem::path const &_path
)
{
	fcppt::either::to_exception(
		fcppt::either::error_from_optional(
			fcppt::filesystem::create_directories_recursive(
				_path
			)
		),
		[
			&_path
		](
			boost::system::error_code const _error
		)
		{
			return
				sge::config::exception{
					FCPPT_TEXT("Failed to create ")
					+
					fcppt::filesystem::path_to_string(
						_path
					)
					+
					FCPPT_TEXT(". Reason: ")
					+
					fcppt::system::error_code_to_string(
						_error
					)
				};
		}
	);

	return
		_path;
}
