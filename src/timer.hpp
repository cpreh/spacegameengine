/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
	frames_type elapsed_frames() const;
	void reset();
	bool expired() const;
	interval_type interval() const { return _interval; }
	interval_type last_time() const { return _last_time; }
	void activate();
	void deactivate();
	bool active() const { return _active; }
private:
	interval_type _interval,
	              _last_time;
	bool          _active;
};

}

#endif
