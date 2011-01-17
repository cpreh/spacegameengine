/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config/make_files.hpp>
#include <sge/config/homedir.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#ifdef FCPPT_WINDOWS_PLATFORM
#include <sge/config/appdir.hpp>
#endif

sge::config::path_vector const
sge::config::make_files(
	fcppt::string const &_config_basename
)
{
#ifdef FCPPT_WINDOWS_PLATFORM
	fcppt::string const suffix(
		FCPPT_TEXT(".txt")
	);

	return
		fcppt::assign::make_container<
			config::path_vector
		>(
			config::appdir()
			/
			(
				_config_basename
				+ suffix
			)
		)
		(
			config::homedir()
			/
			(
				_config_basename
				+ suffix
			)
		);
#elif FCPPT_POSIX_PLATFORM
	fcppt::string const suffix(
		FCPPT_TEXT(".conf")
	);

	return
		fcppt::assign::make_container<
			config::path_vector
		>(
			config::homedir()
			/
			(
				FCPPT_TEXT(".")
				+ _config_basename
				+ suffix
			)
		)
		(
			fcppt::filesystem::path(
				FCPPT_TEXT("/etc")
			)
			/
			(
				_config_basename
				+ suffix
			)
		);
#else
#error "config::make_files not implemented!"
#endif
}
