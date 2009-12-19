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
#include <sge/filesystem/exists.hpp>
#include <sge/filesystem/is_directory.hpp>
#include <sge/filesystem/create_directories_recursive.hpp>
#include <sge/text.hpp>
#include <sge/config.h>
#ifdef SGE_POSIX_PLATFORM
#include <sge/config/homedir.hpp>
#endif

namespace
{

sge::filesystem::path const
try_create_path(
	sge::filesystem::path const &p
)
{
	if(
		!sge::filesystem::exists(
			p
		)
	)
		sge::filesystem::create_directories_recursive(
			p
		);

	if(
		!sge::filesystem::is_directory(
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

sge::filesystem::path const
sge::config::find_config_path(
	string const &appname
)
{
#if defined(SGE_WINDOWS_PLATFORM)
	return try_create_path(
		filesystem::path(
			getenv(
				FCPPT_TEXT("APPDIR")
			)
		)
		/ appname
	);
#elif defined(SGE_POSIX_PLATFORM)
	try
	{
		return try_create_path(
			filesystem::path(
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
			filesystem::path(
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
