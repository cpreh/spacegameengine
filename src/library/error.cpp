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


#include <fcppt/config.h>
#include <sge/library/error.hpp>
#ifdef FCPPT_WINDOWS_PLATFORM
#include <sge/windows/windows.hpp>
#include <sge/windows/format_message.hpp>
#elif FCPPT_POSIX_PLATFORM
#include <fcppt/iconv.hpp>
#include <fcppt/text.hpp>
#include <dlfcn.h>
#else
#error "Implement me!"
#endif

fcppt::string const
sge::library::error()
{
#if defined( FCPPT_POSIX_PLATFORM)
	char const *const err(
		dlerror()
	);

	return err
		? fcppt::iconv(
			err
		)
		: FCPPT_TEXT("no error");
#elif defined(FCPPT_WINDOWS_PLATFORM)
	return sge::windows::format_message(
		GetLastError()
	);
#endif
}
