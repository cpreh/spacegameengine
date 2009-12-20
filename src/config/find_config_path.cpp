/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config/find_config_path.hpp>
#include <sge/config/getenv.hpp>
#include <sge/config/no_such_env_var.hpp>
#include <sge/config/exception.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/is_directory.hpp>
#include <fcppt/filesystem/create_directories_recursive.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config.h>
#ifdef FCPPT_POSIX_PLATFORM
#include <sge/config/homedir.hpp>
#endif

namespace
{

fcppt::filesystem::path const
try_create_path(
	fcppt::filesystem::path const &p
)
{
	if(
		!fcppt::filesystem::exists(
			p
		)
	)
		fcppt::filesystem::create_directories_recursive(
			p
		);

	if(
		!fcppt::filesystem::is_directory(
			p
		)
	)
		throw sge::config::exception(
			p.string()
			+ FCPPT_TEXT(" is not a directory!")
		);

	return p;
}

}

fcppt::filesystem::path const
sge::config::find_config_path(
	fcppt::string const &appname
)
{
#if defined(FCPPT_WINDOWS_PLATFORM)
	return try_create_path(
		fcppt::filesystem::path(
			getenv(
				FCPPT_TEXT("APPDIR")
			)
		)
		/ appname
	);
#elif defined(FCPPT_POSIX_PLATFORM)
	try
	{
		return try_create_path(
			fcppt::filesystem::path(
				getenv(
					FCPPT_TEXT("XDG_CONFIG_PATH")
				)
			)
			/ appname
		);
	}
	catch(
		sge::config::no_such_env_var const &
	)
	{
		return try_create_path(
			fcppt::filesystem::path(
				homedir()
				/ FCPPT_TEXT(".config")
				/ appname
			)
		);
	}
#else
#error "don't know how to find a config path"
#endif
}
