/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/config/app_name.hpp>
#include <sge/config/cache_path.hpp>
#include <sge/src/config/try_create_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <sge/config/homedir.hpp>
#include <sge/config/getenv.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/config/getenv_exn.hpp>
#endif


boost::filesystem::path
sge::config::cache_path(
	sge::config::app_name const &_app_name
)
{
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	return
		sge::config::try_create_path(
			boost::filesystem::path(
				config::getenv_exn(
					FCPPT_TEXT("APPDATA")
				)
			)
			/
			_app_name.get()
		);
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	fcppt::optional_string const xdg_cache_path(
		sge::config::getenv(
			FCPPT_TEXT("XDG_CACHE_HOME")
		)
	);

	boost::filesystem::path const path(
		fcppt::maybe(
			xdg_cache_path,
			[]{
				return
					sge::config::homedir()
					/
					FCPPT_TEXT(".cache");
			},
			[](
				fcppt::string const &_path
			)
			{
				return
					boost::filesystem::path(
						_path
					);
			}
		)
	);

	return
		sge::config::try_create_path(
			path
			/
			_app_name.get()
		);
#else
#error "don't know how to find a cache path"
#endif
}
