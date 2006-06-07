#include "../util.hpp"

#ifdef SGE_WINDOWS_PLATFORM
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#elif SGE_LINUX_PLATFORM
	#include <unistd.h>
#endif

void sge::sleep(const ulong milli_seconds)
{
#ifdef SGE_WINDOWS_PLATFORM
	::Sleep(milli_seconds);
#elif SGE_LINUX_PLATFORM
	::usleep(milli_seconds*1000);
#endif
}

