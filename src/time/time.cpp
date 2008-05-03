/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config.h>
#include <sge/exception.hpp>
#include <sge/time/time.hpp>

#ifdef SGE_POSIX_PLATFORM
#include <sys/time.h>
#elif SGE_WINDOWS_PLATFORM
#include <sge/windows.hpp>
#else
#error "Implement me!"
#endif


#ifdef SGE_WINDOWS_PLATFORM
namespace
{

sge::time::unit query_performance_frequency();
sge::time::unit query_performance_counter();
sge::time::unit large_int_to_time(LARGE_INTEGER);

struct initializer {
	initializer();

	bool use_performance_counter() const;
private:
	bool use_performance_counter_;
} instance;

}

#endif

sge::time::unit sge::time::time()
{
#ifdef SGE_POSIX_PLATFORM
	struct timeval tv;
	struct timezone tz;
	if(gettimeofday(&tv,&tz) != 0)
		throw sge::exception(SGE_TEXT("gettimeofday() failed!"));
	return static_cast<time::unit>(tv.tv_sec * hz() + tv.tv_usec);
#elif SGE_WINDOWS_PLATFORM
	return instance.use_performance_counter()
		? query_performance_counter()
		: static_cast<time::unit>(GetTickCount());
#endif
}

sge::time::unit sge::time::hz()
{
#ifdef SGE_POSIX_PLATFORM
	return 1000 * 1000;
#elif SGE_WINDOWS_PLATFORM
	return instance.use_performance_counter()
	? query_performance_frequency()
	: 1000;
#endif
}

#ifdef SGE_WINDOWS_PLATFORM

namespace
{

sge::time::unit query_performance_frequency()
{
	LARGE_INTEGER ret;
	if(QueryPerformanceFrequency(&ret) == 0)
		throw sge::exception(SGE_TEXT("QueryPerformanceFrequency() failed!"));
	return large_int_to_time(ret);
}

sge::time::unit query_performance_counter()
{
	LARGE_INTEGER ret;
	if(QueryPerformanceCounter(&ret) == 0)
		throw sge::exception(SGE_TEXT("QueryPerformanceCounter() failed!"));
	return large_int_to_time(ret);
}

sge::time::unit large_int_to_time(const LARGE_INTEGER i)
{
	return i.QuadPart; // FIXME
}

initializer::initializer()
: use_performance_counter_(true)
{
	try
	{
		query_performance_frequency();
	}
	catch(const sge::exception&)
	{
		use_performance_counter_ = false;
	}
}

bool initializer::use_performance_counter() const
{
	return use_performance_counter_;
}

}

#endif

