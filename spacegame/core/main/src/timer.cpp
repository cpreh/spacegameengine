#include "../timer.hpp"
#include "../bin_io.hpp"
#include <stdexcept>

namespace {
sge::timer::interval_type read_clock()
{
#ifdef SGE_LINUX_PLATFORM
	struct timeval tv;
	struct timezone tz;
	if(gettimeofday(&tv,&tz) != 0)
		throw std::runtime_error("gettimeofday() failed");
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
#elif SGE_WINDOWS_PLATFORM
	return GetTickCount();
#endif
}
}

sge::timer::timer(interval_type interval)
: interval(interval),
  last_time(read_clock())
{}

sge::timer::frames_type sge::timer::update()
{
	const frames_type f = elapsed_frames();
	if(f > 0)
		reset();
	return f;
}

sge::timer::frames_type sge::timer::elapsed_frames()
{
	const interval_type ntime = read_clock(),
	                    dif = ntime - last_time;
	if(dif < interval)
		return 0;
	return frames_type(dif) / interval;
}

void sge::timer::reset()
{
	last_time = read_clock();
}

