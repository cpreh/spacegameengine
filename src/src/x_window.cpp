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

#include <stdexcept>
#include <boost/assign.hpp>
#include "../iconv.hpp"
#include "../x_window.hpp"

/*sge::x_window::x_window(Display* const dsp, const int _screen, const Window wnd)
 : dsp(dsp),
   _screen(_screen),
   wnd(wnd)
{}*/

sge::x_window::x_window(const window_pos pos, const window_size sz, const string& t, Display* const dsp, const XSetWindowAttributes& attr, const XVisualInfo& vi)
 : dsp(dsp),
   _screen(vi.screen),
   wnd(XCreateWindow(dsp, RootWindow(dsp, screen()), pos.x(), pos.y(), sz.w(), sz.h(), 0, vi.depth, InputOutput, vi.visual, CWColormap | CWOverrideRedirect | CWBorderPixel | CWEventMask, const_cast<XSetWindowAttributes*>(&attr))),
   _fullscreen(attr.override_redirect),
   event_mask(0)
{
	title(t);
}

sge::x_window::~x_window()
{
	XDestroyWindow(dsp,wnd);
}

void sge::x_window::size(const window_size newsize)
{
	XResizeWindow(dsp, wnd, newsize.w(), newsize.h());
}

void sge::x_window::title(const string& t)
{
	XStoreName(dsp, wnd, iconv(t).c_str());
}

sge::x_window::window_size sge::x_window::size() const
{
	Window root_return;
	int x_return,
	    y_return;
	unsigned width_return,
	         height_return,
	         border_width_return,
	         depth_return;

	XGetGeometry(display(), get_window(), &root_return, &x_return, &y_return, &width_return, &height_return, &border_width_return, &depth_return);
	return window_size(width_return,height_return);
}

bool sge::x_window::fullscreen() const
{
	return _fullscreen;
}

Window sge::x_window::get_window() const
{
	return wnd;
}

int sge::x_window::screen() const
{
	return _screen;
}

Display* sge::x_window::display() const
{
	return dsp;
}

boost::signals::connection sge::x_window::register_callback(const x11_event_type event, const x11_callback_type callback)
{
	add_event_mask(event);
	return signals[event].connect(callback);
}

void sge::x_window::dispatch()
{
	XEvent xev;
	while(XPending(display()))
	{
		XNextEvent(display(), &xev);
		if(XFilterEvent(&xev, None))
			continue;
		signals[xev.type](xev);
	}
}

typedef std::map<sge::x_window::x11_event_type, sge::x_window::x11_event_mask_type> mask_map;

const mask_map masks =
boost::assign::map_list_of(KeyPress, KeyPressMask)
                          (KeyRelease, KeyReleaseMask)
                          (ButtonPress, KeyPressMask)
                          (ButtonRelease, KeyReleaseMask)
                          (MotionNotify, PointerMotionMask)
                          (EnterNotify, EnterWindowMask)
                          (LeaveNotify, LeaveWindowMask)
                          (FocusIn, FocusChangeMask)
                          (FocusOut, FocusChangeMask);

void sge::x_window::add_event_mask(const x11_event_type event)
{
	const mask_map::const_iterator it = masks.find(event);
	if(it == masks.end())
		throw std::logic_error("X11 event mask mapping is missing!");

	const x11_event_mask_type mask = it->second;
	if(!(event_mask & mask))
	{
		event_mask |= mask;
		XSetWindowAttributes swa;
		swa.event_mask = event_mask;
		XChangeWindowAttributes(dsp, wnd, CWEventMask, &swa);
	}
}

#endif
