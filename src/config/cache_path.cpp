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


#include "try_create_path.hpp"
#include <sge/config/cache_path.hpp>
#include <sge/config/optional_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/platform.hpp>
#if defined(FCPPT_POSIX_PLATFORM)
#include <sge/config/homedir.hpp>
#include <sge/config/getenv.hpp>
#include <fcppt/optional_impl.hpp>
#elif defined(FCPPT_WINDOWS_PLATFORM)
#include <sge/config/getenv_exn.hpp>
#endif

fcppt::filesystem::path const
sge::config::cache_path(
	fcppt::string const &_appname
)
{
#if defined(FCPPT_WINDOWS_PLATFORM)
	return
		config::try_create_path(
			fcppt::filesystem::path(
				config::getenv_exn(
					FCPPT_TEXT("APPDATA")
				)
			)
			/ _appname
		);
#elif defined(FCPPT_POSIX_PLATFORM)
	optional_string const xdg_cache_path(
		config::getenv(
			FCPPT_TEXT("XDG_CACHE_HOME")
		)
	);

	fcppt::filesystem::path const path(
		xdg_cache_path
		?
			*xdg_cache_path
		:
			config::homedir() / FCPPT_TEXT(".cache")
	);
	
	return
		config::try_create_path(
			path
			/ _appname
		);
#else
#error "don't know how to find a cache path"
#endif
}
