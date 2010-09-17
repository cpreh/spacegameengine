/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config/appdir.hpp>
#include <sge/exception.hpp>
#include <sge/config.h>
#include <fcppt/text.hpp>
#if defined(FCPPT_WINDOWS_PLATFORM)
#include <sge/windows/windows.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/filesystem/remove_filename.hpp>
#include <fcppt/char_type.hpp>
#elif defined(FCPPT_POSIX_PLATFORM)
#include <fcppt/filesystem/remove_filename.hpp>
#include <fcppt/filesystem/readlink.hpp>
#include <fcppt/filesystem/exists.hpp>
#endif

fcppt::filesystem::path const
sge::config::appdir()
{
#if defined(FCPPT_WINDOWS_PLATFORM)
	typedef fcppt::container::raw_vector<
		fcppt::char_type
	> buffer_type;
	
	buffer_type buf(32768);

	if(
		!::GetModuleFileName(
			NULL,
			buf.data(),
			static_cast<DWORD>(buf.size())
		)
	)
		throw exception(
			FCPPT_TEXT("GetModuleFileName() failed!")
		);

	return fcppt::filesystem::remove_filename(
		fcppt::string(
			buf.data()
		)
	);
#elif defined(FCPPT_POSIX_PLATFORM)
	fcppt::filesystem::path const self(
		"/proc/self/exe"
	);

	if(
		!fcppt::filesystem::exists(
			self
		)
	)
		throw exception(
			FCPPT_TEXT("/prof/self/exe does not exist")
		);

	return fcppt::filesystem::remove_filename(
		fcppt::filesystem::readlink(
			self
		)
	);
#else
	throw exception(
		FCPPT_TEXT("Can't find the application's path!")
	);
#endif
}
