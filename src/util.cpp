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
#include <sge/util.hpp>

#ifdef SGE_WINDOWS_PLATFORM
#include <sge/windows.hpp>
#elif SGE_POSIX_PLATFORM
#include <unistd.h>
#endif

void sge::sleep(const unsigned long milli_seconds)
{
#ifdef SGE_WINDOWS_PLATFORM
	Sleep(milli_seconds);
#elif SGE_POSIX_PLATFORM
	usleep(static_cast<__useconds_t>(milli_seconds*1000));
#else
#error "Implement me!"
#endif
}

