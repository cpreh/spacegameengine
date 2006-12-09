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


#include "../types.hpp"
#ifdef SGE_LINUX_PLATFORM

#include "../x_window.hpp"
sge::x_window::x_window(const window_size sz, const std::string& _title, Display* const dsp, const int screen, XVisualInfo* const vi, Colormap& cmap)
 : sz(sz), _title(_title), _active(false), dsp(dsp), screen(screen)
{
	XSetWindowAttributes swa;
	swa.colormap = cmap;
	swa.border_pixel = 0;
	swa.background_pixel = 0;
//	swa.override_redirect = False;
	swa.event_mask = FocusChangeMask | KeyPressMask | KeyReleaseMask | PropertyChangeMask | StructureNotifyMask | KeymapStateMask | PointerMotionMask;
	wnd = XCreateWindow(dsp,RootWindow(dsp,vi->screen),0,0,sz.w,sz.h,0,vi->depth, InputOutput, vi->visual, CWColormap /*| CWOverrideRedirect*/ | CWBorderPixel | CWEventMask, &swa);
	XStoreName(dsp,wnd,_title.c_str());
}

sge::x_window::~x_window()
{
	XDestroyWindow(dsp,wnd);
}

void sge::x_window::size(const window_size newsize)
{
	XResizeWindow(dsp,wnd,newsize.w,newsize.h);
}

void sge::x_window::title(const std::string& t)
{
	_title = t;
	XStoreName(dsp,wnd,_title.c_str());
}

#endif
