/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/src/plugin/library/error.hpp>
#include <fcppt/config/platform.hpp>
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/format_message.hpp>
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <dlfcn.h>
#include <fcppt/config/external_end.hpp>
#else
#error "Implement me!"
#endif

fcppt::string const
sge::plugin::library::error()
{
#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
	char const *const err(
		dlerror()
	);

	return
		err
		?
			fcppt::from_std_string(
				err
			)
		:
			FCPPT_TEXT("no error");
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	return
		awl::backends::windows::format_message(
			::GetLastError()
		);
#endif
}
