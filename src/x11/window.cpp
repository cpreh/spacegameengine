/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/mainloop/io_service.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/optional_impl.hpp>
#include <boost/assign/list_of.hpp>
#include <X11/Xlibint.h>

sge::x11::window::window(
	pos_type const &_pos,
	dim_type const &_size,
	fcppt::string const &_title,
	display_ptr const _display,
	int const _screen,
	int const _depth,
	bool const _fullscreen,
	const_visual_ptr const _visual,
	colormap_ptr const _colormap,
	fcppt::string const &_class_name,
	sge::mainloop::io_service_ptr const _io_service
)
:
	io_service_(
		_io_service
	),
	// FIXME: here we make sure the dispatcher is destroyed AFTER
	// the display, because asio closes the socket (which it shouldn't!)
	dispatcher_(
		_io_service
		?
			_io_service->create_dispatcher(
				_display->get()->fd,
				std::tr1::bind(
					&window::dispatch,
					this
				)
			)
		:
			mainloop::dispatcher_ptr()
	),
	display_(_display),
	visual_(_visual),
	colormap_(_colormap),
	screen_(_screen),
	window_(0),
	fullscreen_(_fullscreen),
	event_mask_(0),
	hints_(),
	size_hints_(
		_size.w(),
		_size.h(),
		_size.w(),
		_size.h()
	),
	class_hint_(
		_title,
		_class_name
	),
	signals_()
{
	XSetWindowAttributes swa;
	swa.colormap = _colormap->get();
	swa.border_pixel = 0;
	swa.background_pixel = 0;
	swa.override_redirect = fullscreen_ ? True : False;
	swa.event_mask = StructureNotifyMask;

	// always returns a handle
	window_ = XCreateWindow(
		display_->get(),
		XRootWindow(
			display_->get(),
			screen()
		),
		_pos.x(),
		_pos.y(),
		_size.w(),
		_size.h(),
		0,
		_depth,
		InputOutput,
		visual_->get(),
		CWColormap | CWOverrideRedirect | CWBorderPixel | CWEventMask,
		const_cast<XSetWindowAttributes *>(&swa)
	);

	hints();
	set_size_hints();
	set_class_hint();

	XStoreName(
		display_->get(),
		window_,
		fcppt::to_std_string(
			_title
		).c_str()
	);
}

sge::x11::window::~window()
{
	XDestroyWindow(
		display_->get(),
		window_
	);
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
			display_->get(),
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

	return
		dim_type(
			width_return,
			height_return
		);
}

void
sge::x11::window::show()
{
	map();

	display()->sync();
}

sge::mainloop::io_service_ptr const
sge::x11::window::io_service() const
{
	return io_service_;
}

bool
sge::x11::window::fullscreen() const
{
	return fullscreen_;
}

Window
sge::x11::window::get() const
{
	return window_;
}

int
sge::x11::window::screen() const
{
	return screen_;
}

sge::x11::display_ptr const
sge::x11::window::display() const
{
	return display_;
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
	XMapWindow(
		display_->get(),
		get()
	);
}

void
sge::x11::window::map_raised()
{
	// always returns 1
	XMapRaised(
		display_->get(),
		get()
	);
}

fcppt::signal::auto_connection
sge::x11::window::register_callback(
	event_type const event,
	callback_type const &callback
)
{
	add_event_mask(event);
	return signals_[event].connect(callback);
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
			display_->get(),
			get(),
			event_mask_,
			&xev
		)
	)
	{
		if(
			XFilterEvent(
				&xev,
				None
			)
		)
			continue;

		signals_[xev.type](xev);
	}
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

	if(!(event_mask_ & mask))
	{
		event_mask_ |= mask;
		
		XSetWindowAttributes swa;
		
		swa.event_mask = event_mask_;

		// always returns 1
		XChangeWindowAttributes(
			display_->get(),
			get(),
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
		display_->get(),
		get(),
		hints_.get()
	);
}

void
sge::x11::window::set_size_hints()
{
	// always returns 1
	XSetWMNormalHints(
		display_->get(),
		get(),
		size_hints_.get()
	);
}

void
sge::x11::window::set_class_hint()
{
	// always returns 1
	XSetClassHint(
		display_->get(),
		get(),
		class_hint_.get()
	);
}
