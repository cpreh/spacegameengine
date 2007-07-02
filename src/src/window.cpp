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


#include "../window.hpp"
#if   defined(SGE_WINDOWS_PLATFORM)
#	include "../win32_window.hpp"
#elif defined(SGE_LINUX_PLATFORM)
#	include "../x_window.hpp"
#else
#	error implement
#endif

sge::window::size_type sge::window::width() const
{
	return size().w();
}

sge::window::size_type sge::window::height() const
{
	return size().h();
}

void sge::window::dispatch()
{
#if   defined(SGE_WINDOWS_PLATFORM)
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
#elif defined(SGE_LINUX_PLATFORM)
	XEvent xev;
	std::set<sge::x_window*>::iterator
		b = sge::x_window::instances.begin(),
		e = sge::x_window::instances.end();
	while (b != e)
	{
		while(XPending((*b)->display()))
		{
			XNextEvent((*b)->display(), &xev);
			if(XFilterEvent(&xev, None))
				continue;
			signals[xev.type](xev);
		}
		++b;
	}
#endif
}
