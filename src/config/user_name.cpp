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


#include <sge/config/user_name.hpp>
#include <fcppt/config/platform.hpp>
#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <sge/config/exception.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/error/strerrno.hpp>
#include <fcppt/text.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <cerrno>
#include <fcppt/config/external_end.hpp>
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/config/exception.hpp>
#include <sge/config/exception.hpp>
#include <awl/backends/windows/format_message.hpp>
#include <fcppt/text.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <windows.h>
#include <lmcons.h>
#include <fcppt/config/external_end.hpp>
#endif


fcppt::string
sge::config::user_name()
{
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	typedef
	std::array<fcppt::char_type,UNLEN+1>
	raw_character_sequence;

	raw_character_sequence raw_characters;
	// I don't know if the size argument can be NULL.
	DWORD size =
		static_cast<DWORD>(
			raw_characters.size());

	if(!GetUserName(raw_characters.data(),&size))
		throw
			sge::config::exception(
				FCPPT_TEXT("Couldn't get user name: ")+
				awl::backends::windows::format_message(
					GetLastError()));

	return
		fcppt::string(
			raw_characters.data());
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	typedef
	fcppt::container::raw_vector<char>
	raw_byte_sequence;

	raw_byte_sequence buf;

	long const bufsize =
		sysconf(
			_SC_GETPW_R_SIZE_MAX);

	if (bufsize == -1)          /* Value was indeterminate */
		throw
			sge::config::exception(
				FCPPT_TEXT("Couldn't determine maximum user name length"));

	buf.resize(
		static_cast<raw_byte_sequence::size_type>(
			bufsize));

	struct passwd pwd;
	struct passwd *result;

	int const error_code =
		getpwuid_r(
			getuid(),
			&pwd,
			buf.data(),
			buf.size(),
			&result);

	if(error_code)
		throw
			sge::config::exception(
				FCPPT_TEXT("Couldn't determine user name: ")+
				fcppt::error::strerrno());

	return
		fcppt::from_std_string(
			std::string(
				pwd.pw_name));
#else
#error "don't know how to find a config path"
#endif
}
