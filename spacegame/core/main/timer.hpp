#ifndef SGE_TIMER_HPP_INCLUDED
#define SGE_TIMER_HPP_INCLUDED

#include "./types.hpp"
#ifdef SGE_LINUX_PLATFORM
#include <sys/time.h>
#elif SGE_WINDOWS_PLATFORM
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace sge
{

class timer {
public:
	typedef float frames_type;
#ifdef SGE_LINUX_PLATFORM
	typedef suseconds_t interval_type;
#elif SGE_WINDOWS_PLATFORM
	typedef DWORD interval_type;
#endif

	timer(interval_type interval);
	frames_type update();
	frames_type elapsed_frames();
	void reset();
	interval_type interval() const { return _interval; }
	interval_type last_time() const { return _last_time; }
private:
	interval_type _interval,
	              _last_time;
};

}

#endif
