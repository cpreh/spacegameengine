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
#include <sge/time.hpp>

#ifdef SGE_LINUX_PLATFORM
#include <sys/time.h>
#elif SGE_WINDOWS_PLATFORM
#include <sge/windows.hpp>
#endif


#ifdef SGE_WINDOWS_PLATFORM
namespace
{

sge::time_type query_performance_frequency();
sge::time_type query_performance_counter();
sge::time_type large_int_to_time(LARGE_INTEGER);

struct initializer {
	initializer();

	bool use_performance_counter() const;
private:
	bool use_performance_counter_;
} instance;

}

#endif

sge::time_type sge::time()
{
#ifdef SGE_LINUX_PLATFORM
	struct timeval tv;
	struct timezone tz;
	if(gettimeofday(&tv,&tz) != 0)
		throw sge::exception(SGE_TEXT("gettimeofday() failed!"));
	return static_cast<time_type>(tv.tv_sec * second() + tv.tv_usec);
#elif SGE_WINDOWS_PLATFORM
	return instance.use_performance_counter()
		? query_performance_counter()
		: static_cast<time_type>(GetTickCount());
#endif
}

sge::time_type sge::second()
{
#ifdef SGE_LINUX_PLATFORM
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

sge::time_type query_performance_frequency()
{
	LARGE_INTEGER ret;
	if(QueryPerformanceFrequency(&ret) == 0)
		throw sge::exception(SGE_TEXT("QueryPerformanceFrequency() failed!"));
	return large_int_to_time(ret);
}

sge::time_type query_performance_counter()
{
	LARGE_INTEGER ret;
	if(QueryPerformanceCounter(&ret) == 0)
		throw sge::exception(SGE_TEXT("QueryPerformanceCounter() failed!"));
	return large_int_to_time(ret);
}

sge::time_type large_int_to_time(const LARGE_INTEGER i)
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

