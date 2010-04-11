/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/x11/error.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/optional_impl.hpp>
#include <boost/assign/list_of.hpp>

sge::x11::window::window(
	pos_type const &pos,
	dim_type const &sz,
	fcppt::string const &t,
	display_ptr const dsp,
	int const screen_,
	int const depth,
	bool const fullscreen_,
	const_visual_ptr const visual_,
	colormap_ptr const colormap_,
	fcppt::string const &class_name
)
:
	dsp(dsp),
	visual_(visual_),
	colormap_(colormap_),
	screen_(screen_),
	wnd(0),
	fullscreen_(fullscreen_),
	event_mask(0),
	hints_(),
	size_hints_(
		sz.w(),
		sz.h(),
		sz.w(),
		sz.h()
	),
	class_hint_(
		t,
		class_name
	)
{
	XSetWindowAttributes swa;
	swa.colormap = colormap_->get();
	swa.border_pixel = 0;
	swa.background_pixel = 0;
	swa.override_redirect = fullscreen_ ? True : False;
	swa.event_mask = StructureNotifyMask;

	// always returns a handle
	wnd = XCreateWindow(
		dsp->get(),
		XRootWindow(
			dsp->get(),
			screen()
		),
		pos.x(),
		pos.y(),
		sz.w(),
		sz.h(),
		0,
		depth,
		InputOutput,
		visual_->get(),
		CWColormap | CWOverrideRedirect | CWBorderPixel | CWEventMask,
		const_cast<XSetWindowAttributes *>(&swa)
	);

	hints();
	set_size_hints();
	set_class_hint();

	XStoreName(
		dsp_(),
		wnd,
		fcppt::to_std_string(t).c_str()
	);
}

sge::x11::window::~window()
{
	XDestroyWindow(dsp_(), wnd);
}

sge::x11::window::dim_type const
sge::x11::window::size() const
{
	Window root_return;
	int
		x_return,
		y_return;
	unsigned
		width_return,
		height_return,
		border_width_return,
		depth_return;

	if(
		XGetGeometry(
			dsp_(),
			get(),
			&root_return,
			&x_return,
			&y_return,
			&width_return,
			&height_return,
			&border_width_return,
			&depth_return
		) == 0
	)
		throw sge::exception(
			FCPPT_TEXT("XGetGeometry() failed!")
		);

	return dim_type(
		width_return,
		height_return
	);
}

bool
sge::x11::window::fullscreen() const
{
	return fullscreen_;
}

Window
sge::x11::window::get() const
{
	return wnd;
}

int
sge::x11::window::screen() const
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

void
sge::x11::window::map()
{
	// always returns 1
	XMapWindow(dsp->get(), get());
}

void
sge::x11::window::map_raised()
{
	// always returns 1
	XMapRaised(dsp->get(), get());
}

fcppt::signal::auto_connection
sge::x11::window::register_callback(
	event_type const event,
	callback_type const &callback
)
{
	add_event_mask(event);
	return signals[event].connect(callback);
}

namespace
{

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

}

void
sge::x11::window::dispatch()
{
	// check for recent errors
	{
		optional_error const error_(
			error()
		);

		if(
			error_
		)
			throw exception(
				FCPPT_TEXT("Xerror event caught: ")
				+ *error_
			);
	}

	XEvent xev;

	while(
		XCheckWindowEvent(
			dsp_(),
			get(),
			event_mask,
			&xev
		)
	)
	{
		if(XFilterEvent(&xev, None))
			continue;

		signals[xev.type](xev);
	}
}

Display *
sge::x11::window::dsp_() const
{
	return display()->get();
}

void
sge::x11::window::add_event_mask(
	event_type const event
)
{
	mask_map::const_iterator const it(
		masks.find(
			event
		)
	);

	if(it == masks.end())
		throw exception(
			FCPPT_TEXT("X11 event mask mapping is missing!")
		);

	event_mask_type const mask = it->second;

	if(!(event_mask & mask))
	{
		event_mask |= mask;
		
		XSetWindowAttributes swa;
		
		swa.event_mask = event_mask;

		// always returns 1
		XChangeWindowAttributes(
			dsp_(),
			wnd,
			CWEventMask,
			&swa
		);
	}
}

void
sge::x11::window::hints()
{
	// always returns 1
	XSetWMHints(
		dsp_(),
		get(),
		hints_.get()
	);
}

void
sge::x11::window::set_size_hints()
{
	// always returns 1
	XSetWMNormalHints(
		dsp_(),
		get(),
		size_hints_.get()
	);
}

void
sge::x11::window::set_class_hint()
{
	// always returns 1
	XSetClassHint(
		dsp_(),
		get(),
		class_hint_.get()
	);
}
