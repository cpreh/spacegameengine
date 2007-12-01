/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (simon.stienen@slashlife.org)

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


#include "../types.hpp"
#ifdef SGE_LINUX_PLATFORM

#include <iostream>
#include <ostream>
#include <boost/array.hpp>
#include <boost/assign.hpp>
#include "../exception.hpp"
#include "../iconv.hpp"
#include "../x_window.hpp"

int handler(Display*, XErrorEvent*);

namespace {
struct init_error_handler {
	init_error_handler()
	{
		XSetErrorHandler(handler);
	}
} instance;
}

sge::x_window::x_window(const window_pos pos,
                        const window_size sz,
                        const string& t,
                        const x_display_ptr dsp,
                        const XSetWindowAttributes& attr,
                        const XVisualInfo& vi)
 : dsp(dsp),
   _screen(vi.screen),
   wnd(XCreateWindow(dsp->get(),
                     RootWindow(dsp->get(), screen()),
                     pos.x(),
                     pos.y(),
                     sz.w(),
                     sz.h(),
                     0,
                     vi.depth,
                     InputOutput,
                     vi.visual,
                     CWColormap | CWOverrideRedirect | CWBorderPixel | CWEventMask,
                     const_cast<XSetWindowAttributes*>(&attr))),
   _fullscreen(attr.override_redirect),
   event_mask(0)
{
	title(t);
	instances.insert(this);
}

sge::x_window::x_window(Display *const dsp, const int screen_, Window wnd)
 : dsp(new x_display(dsp, x_display::wrap_tag())),
   _screen(screen_),
   wnd(wnd)
{}

/*sge::x_window::x_window()
 : dsp(new x_display()),
   _screen(DefaultScreen(dsp->get())),
   wnd(XCreateSimpleWindow())
{}*/

sge::x_window::~x_window()
{
	instances.erase(this);
	XDestroyWindow(dsp_(), wnd);
}

void sge::x_window::size(const window_size newsize)
{
	XResizeWindow(dsp_(), wnd, newsize.w(), newsize.h());
}

void sge::x_window::title(const string& t)
{
	XStoreName(dsp_(), wnd, iconv(t).c_str());
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

	XGetGeometry(dsp_(), get_window(), &root_return, &x_return, &y_return, &width_return, &height_return, &border_width_return, &depth_return);
	return window_size(width_return, height_return);
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

sge::x_display_ptr sge::x_window::display() const
{
	return dsp;
}

Display* sge::x_window::dsp_() const
{
	return display()->get();
}

boost::signals::connection sge::x_window::register_callback(const x11_event_type event, const x11_callback_type callback)
{
	add_event_mask(event);
	return signals[event].connect(callback);
}

typedef std::map<sge::x_window::x11_event_type, sge::x_window::x11_event_mask_type> mask_map;

const mask_map masks =
boost::assign::map_list_of(KeyPress, KeyPressMask)
                          (KeyRelease, KeyReleaseMask)
                          (ButtonPress, ButtonPressMask)
                          (ButtonRelease, ButtonReleaseMask)
                          (MotionNotify, PointerMotionMask)
                          (EnterNotify, EnterWindowMask)
                          (LeaveNotify, LeaveWindowMask)
                          (FocusIn, FocusChangeMask)
                          (FocusOut, FocusChangeMask)
                          (MapNotify, StructureNotifyMask)
                          (UnmapNotify, StructureNotifyMask)
                          (ResizeRequest, ResizeRedirectMask)
                          (ConfigureRequest, SubstructureRedirectMask);

void sge::x_window::add_event_mask(const x11_event_type event)
{
	const mask_map::const_iterator it = masks.find(event);
	if(it == masks.end())
		throw exception("X11 event mask mapping is missing!");

	const x11_event_mask_type mask = it->second;
	if(!(event_mask & mask))
	{
		event_mask |= mask;
		XSetWindowAttributes swa;
		swa.event_mask = event_mask;
		XChangeWindowAttributes(dsp_(), wnd, CWEventMask, &swa);
	}
}

void sge::window::dispatch()
{
	XEvent xev;
	const x_window::instance_map::iterator e = sge::x_window::instances.end();
	for (x_window::instance_map::iterator b = sge::x_window::instances.begin(); b != e; ++b)
	{
		x_window& wnd = **b;
		while(XCheckWindowEvent(wnd.dsp_(), wnd.get_window(), wnd.event_mask, &xev))
		{
			if(XFilterEvent(&xev, None))
				continue;

			wnd.signals[xev.type](xev);
		}
	}
}

/*sge::window_ptr sge::create_window()
{
	return window_ptr(new x_window());
}*/

int handler(Display* const d, XErrorEvent* const e)
{
	boost::array<char,1024> buf;
	XGetErrorText(d, e->error_code,buf.c_array(), buf.size());
	std::cerr << "X Error: " << buf.data() << '\n';
	return 0;
}

sge::window::window_pos sge::x_window::viewport_offset() const {
	return window_pos(0,0);
}

sge::x_window::instance_map sge::x_window::instances;

#endif
