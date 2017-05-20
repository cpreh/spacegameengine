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


#include <sge/config/exception.hpp>
#include <sge/config/impl/try_create_path.hpp>
#include <fcppt/either/error_from_optional.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/filesystem/create_directories_recursive.hpp>
#include <fcppt/filesystem/create_directory_error.hpp>
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
					fcppt::filesystem::create_directory_error(
						_path,
						_error
					)
				};
		}
	);

	return
		_path;
}
