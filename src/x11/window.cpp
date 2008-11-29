/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (s.stienen@slashlife.org)

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


#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <sge/x11/visual.hpp>
#include <sge/x11/colormap.hpp>
#include <sge/x11/sentry.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <boost/assign/list_of.hpp>

sge::x11::window::window(
	pos_type const &pos,
	dim_type const &sz,
	string const &t,
	display_ptr const dsp,
	int const screen_,
	int const depth,
	bool const fullscreen_,
	const_visual_ptr const visual_,
	colormap_ptr const colormap_)
:
	dsp(dsp),
	visual_(visual_),
	colormap_(colormap_),
	screen_(screen_),
	wnd(0),
	fullscreen_(fullscreen_),
	event_mask(0),
	hints_()
{
	SGE_X11_SENTRY

	XSetWindowAttributes swa;
	swa.colormap = colormap_->get();
	swa.border_pixel = 0;
	swa.background_pixel = 0;
	swa.override_redirect = fullscreen_ ? True : False;
	swa.event_mask = StructureNotifyMask;

	wnd = XCreateWindow(
		dsp->get(),
		XRootWindow(
			dsp->get(),
			screen()),
		pos.x(),
		pos.y(),
		sz.w(),
		sz.h(),
		0,
		depth,
		InputOutput,
		visual_->get(),
		CWColormap | CWOverrideRedirect | CWBorderPixel | CWEventMask,
		const_cast<XSetWindowAttributes *>(&swa)),

	XSetWMHints(
		display()->get(),
		get(),
		hints_.get());	

	title(t);
}

sge::x11::window::~window()
{
	SGE_X11_SENTRY

	XDestroyWindow(dsp_(), wnd);
}

void sge::x11::window::size(
	dim_type const &newsize)
{
	SGE_X11_SENTRY

	XResizeWindow(dsp_(), wnd, newsize.w(), newsize.h());
}

void sge::x11::window::title(
	string const &t)
{
	SGE_X11_SENTRY

	XStoreName(dsp_(), wnd, iconv(t).c_str());
}

sge::x11::window::dim_type const
sge::x11::window::size() const
{
	SGE_X11_SENTRY

	Window root_return;
	int x_return,
	    y_return;
	unsigned width_return,
	         height_return,
	         border_width_return,
	         depth_return;

	XGetGeometry(
		dsp_(),
		get(),
		&root_return,
		&x_return,
		&y_return,
		&width_return, 
		&height_return,
		&border_width_return,
		&depth_return);
	return dim_type(width_return, height_return);
}

bool sge::x11::window::fullscreen() const
{
	return fullscreen_;
}

Window sge::x11::window::get() const
{
	return wnd;
}

int sge::x11::window::screen() const
{
	return screen_;
}

sge::x11::display_ptr const
sge::x11::window::display() const
{
	return dsp;
}

sge::x11::const_visual_ptr const
sge::x11::window::visual() const
{
	return visual_;
}

void sge::x11::window::map()
{
	SGE_X11_SENTRY

	XMapWindow(dsp->get(), get());
}

void sge::x11::window::map_raised()
{
	SGE_X11_SENTRY

	XMapRaised(dsp->get(), get());
}

Display* sge::x11::window::dsp_() const
{
	return display()->get();
}

boost::signals::connection
sge::x11::window::register_callback(
	event_type const event,
	callback_type const &callback)
{
	add_event_mask(event);
	return signals[event].connect(callback);
}

typedef std::map<
	sge::x11::window::event_type,
	sge::x11::window::event_mask_type
> mask_map;

mask_map const masks =
boost::assign::map_list_of
	(KeyPress, KeyPressMask)
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
	(ConfigureRequest, SubstructureRedirectMask)
	(ConfigureNotify, StructureNotifyMask);

void sge::x11::window::add_event_mask(
	event_type const event)
{
	mask_map::const_iterator const it = masks.find(event);
	if(it == masks.end())
		throw exception(
			SGE_TEXT("X11 event mask mapping is missing!"));

	event_mask_type const mask = it->second;
	if(!(event_mask & mask))
	{
		event_mask |= mask;
		XSetWindowAttributes swa;
		swa.event_mask = event_mask;
		XChangeWindowAttributes(dsp_(), wnd, CWEventMask, &swa);
	}
}

void sge::x11::window::dispatch()
{
	SGE_X11_SENTRY

	XEvent xev;
	while(XCheckWindowEvent(dsp_(), get(), event_mask, &xev))
	{
		if(XFilterEvent(&xev, None))
			continue;
		signals[xev.type](xev);
	}
}

sge::window::pos_type const
sge::x11::window::viewport_offset() const
{
	return pos_type::null();
}
