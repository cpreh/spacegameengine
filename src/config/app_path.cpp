/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/config/app_path.hpp>
#include <sge/config/exception.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/src/core/include_windows.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/char_type.hpp>
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <fcppt/config/external_end.hpp>
#else
#error "Implement me!"
#endif


boost::filesystem::path
sge::config::app_path()
{
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	typedef fcppt::container::raw_vector<
		fcppt::char_type
	> buffer_type;

	buffer_type buf(
		32768u
	);

	if(
		!::GetModuleFileName(
			NULL,
			buf.data(),
			static_cast<
				DWORD
			>(
				buf.size()
			)
		)
	)
		throw sge::config::exception(
			FCPPT_TEXT("GetModuleFileName() failed!")
		);

	return
		boost::filesystem::path(
			fcppt::string(
				buf.data()
			)
		).parent_path();
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	boost::filesystem::path const self(
		"/proc/self/exe"
	);

	if(
		!boost::filesystem::exists(
			self
		)
	)
		throw sge::config::exception(
			FCPPT_TEXT("/prof/self/exe does not exist")
		);

	return
		boost::filesystem::read_symlink(
			self
		).parent_path();
#else
#error "Implement me!"
#endif
}
