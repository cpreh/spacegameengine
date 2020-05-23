//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/homedir.hpp>
#include <sge/config/impl/getenv_exn.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


std::filesystem::path
sge::config::homedir()
{
#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
	return
		sge::config::impl::getenv_exn(
			FCPPT_TEXT("HOME")
		);
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	return
		sge::config::impl::getenv_exn(
			FCPPT_TEXT("USERPROFILE")
		);
#else
#error "Don't know how to get the homedir"
#endif
}
