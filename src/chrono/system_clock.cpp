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


#include <sge/chrono/system_clock.hpp>
#include <sge/chrono/time_point_impl.hpp>
#include <sge/config.h>
#ifdef SGE_WINDOWS_PLATFORM
#include <sge/windows/windows.hpp>
#elif SGE_POSIX_PLATFORM
#include <sge/chrono/clock_failure.hpp>
#include <sge/text.hpp>
#include <sys/time.h>
#else
#error "system_clock implementation missing"
#endif

sge::chrono::system_clock::time_point
sge::chrono::system_clock::now()
{
#ifdef SGE_WINDOWS_PLATFORM
	FILETIME ret;
	GetSystemTimeAsFileTime(
		&ret
	);

	ULARGE_INTEGER large_int;
	large_int.u.LowPart = ret.dwLowDateTime;
	large_int.u.HighPart = ret.dwHighDateTime;

	return time_point(
		duration(
			large_int.QuadPart
		)
	);
#elif SGE_POSIX_PLATFORM
	struct timeval tv;
	struct timezone tz;

	if(
		gettimeofday(
			&tv,
			&tz
		) != 0
	)
		throw clock_failure(
			SGE_TEXT("gettimeofday() failed")
		);

	return time_point(
		duration(
			tv.tv_sec * period::den + tv.tv_usec
		)
	);
#endif
}


std::time_t
sge::chrono::system_clock::to_time_t(
	time_point const &point_
)
{
	return point_.time_since_epoch().count() / duration::period::den;
}

sge::chrono::system_clock::time_point
sge::chrono::system_clock::from_time_t(
	std::time_t const tm_
)
{
	return time_point(
		duration(
			tm_ * duration::period::den
		)
	);
}
