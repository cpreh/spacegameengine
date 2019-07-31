//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/app_name.hpp>
#include <sge/config/cache_path.hpp>
#include <sge/config/impl/try_create_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <sge/config/homedir.hpp>
#include <sge/config/getenv.hpp>
#include <fcppt/optional/maybe.hpp>
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
		sge::config::impl::try_create_path(
			boost::filesystem::path(
				sge::config::getenv_exn(
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
		fcppt::optional::maybe(
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
		sge::config::impl::try_create_path(
			path
			/
			_app_name.get()
		);
#else
#error "don't know how to find a cache path"
#endif
}
