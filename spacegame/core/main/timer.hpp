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

		SGECOREDLLAPI timer(interval_type interval);
		SGECOREDLLAPI frames_type update();
		SGECOREDLLAPI frames_type elapsed_frames();
		SGECOREDLLAPI void reset();
		SGECOREDLLAPI interval_type get_interval() const { return interval; }
		SGECOREDLLAPI interval_type get_last_time() const { return last_time; }
	private:
		interval_type interval;
		interval_type last_time;
	};
}

#endif
