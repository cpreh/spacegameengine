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


#include "../mouse.hpp"
#include "../pointer.hpp"
#include "../mouse_grab.hpp"
#include "../mouse_keys.hpp"
#include <X11/Xlib.h>
#include <sge/log/global.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/key_type.hpp>
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

namespace
{

sge::input::key_type
mouse_key(
	unsigned x11code
);

}

sge::x11input::mouse::mouse(
	x11::window_ptr const wnd,
	input::callback const &callback
)
:
	wnd(wnd),
	black_(
		wnd->display(),
		XDefaultColormap(
			wnd->display()->get(),
			wnd->screen()
		), // TODO: do we have to release this?
		FCPPT_TEXT("black")
	),
	no_bmp_(
		wnd->display(),
		wnd->get()
	),
	cur(
		wnd->display(),
		no_bmp_.get(),
		black_.get()
	),
	callback(callback),
	mouse_last(),
	dga_(wnd)
{
	connections.connect(
		wnd->register_callback(
			MotionNotify,
			std::tr1::bind(
				&mouse::on_motion,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections.connect(
		wnd->register_callback(
			ButtonPress,
			std::tr1::bind(
				&mouse::on_button_down,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections.connect(
		wnd->register_callback(
			ButtonRelease,
			std::tr1::bind(
				&mouse::on_button_up,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	if(!dga_.useable())
		mouse_last = get_pointer(wnd);
}

sge::x11input::mouse::~mouse()
{
}

void
sge::x11input::mouse::grab()
{
	dga_.enable(true);

	grab_.reset(
		new mouse_grab(
			wnd,
			cur
		)
	);
}

void
sge::x11input::mouse::ungrab()
{
	grab_.reset();

	dga_.enable(false);
}

void
sge::x11input::mouse::on_motion(
	XEvent const &e
)
{
	if(dga_.useable())
		dga_motion(e);
	else
		warped_motion(e);
}

void
sge::x11input::mouse::on_button_down(
	XEvent const &e
)
{
	callback(
		input::key_pair(
			mouse_key(
				e.xbutton.button
			),
			1
		)
	);
}

void
sge::x11input::mouse::on_button_up(
	XEvent const &e
)
{
	callback(
		input::key_pair(
			mouse_key(
				e.xbutton.button
			),
			0
		)
	);
}

void
sge::x11input::mouse::dga_motion(
	XEvent xevent
)
{
	mouse_coordinate_t
		dx = xevent.xmotion.x_root,
		dy = xevent.xmotion.y_root;

	while(
		XCheckTypedEvent(
			wnd->display()->get(),
			MotionNotify,
			&xevent
		)
	)
	{
		dx += xevent.xmotion.x_root;
		dy += xevent.xmotion.y_root;
	}

	private_mouse_motion(dx, dy);
}

void
sge::x11input::mouse::warped_motion(
	XEvent xevent
)
{
	if(!grab_)
		return;

	mouse_coordinate_t const
		MOUSE_FUDGE_FACTOR = 8,
		w = wnd->size().w(),
		h = wnd->size().h();

	mouse_coordinate_t
		deltax = xevent.xmotion.x - mouse_last.x(),
		deltay = xevent.xmotion.y - mouse_last.y();

	mouse_last.x() = xevent.xmotion.x;
	mouse_last.y() = xevent.xmotion.y;

	private_mouse_motion(
		deltax,
		deltay);

	if (
		!((xevent.xmotion.x < MOUSE_FUDGE_FACTOR) ||
		(xevent.xmotion.x > (w-MOUSE_FUDGE_FACTOR)) ||
		(xevent.xmotion.y < MOUSE_FUDGE_FACTOR) ||
		(xevent.xmotion.y > (h-MOUSE_FUDGE_FACTOR)) )
	)
		return;

	while(
		XCheckTypedEvent(
			wnd->display()->get(),
			MotionNotify,
			&xevent
		)
	)
	{
		deltax = xevent.xmotion.x - mouse_last.x();
		deltay = xevent.xmotion.y - mouse_last.y();

		mouse_last.x() = xevent.xmotion.x;
		mouse_last.y() = xevent.xmotion.y;

		private_mouse_motion(deltax, deltay);
	}

	mouse_last.x() = w / 2;
	mouse_last.y() = h / 2;

	warp_pointer(
		wnd,
		mouse_last);

	for(unsigned i = 0; i < 10; ++i)
	{
		XMaskEvent(
			wnd->display()->get(),
			PointerMotionMask,
			&xevent);

		if (
			(xevent.xmotion.x > mouse_last.x() - MOUSE_FUDGE_FACTOR) &&
			(xevent.xmotion.x < mouse_last.x() + MOUSE_FUDGE_FACTOR) &&
			(xevent.xmotion.y > mouse_last.y() - MOUSE_FUDGE_FACTOR) &&
			(xevent.xmotion.y < mouse_last.y() + MOUSE_FUDGE_FACTOR)
		)
			return;

	}

	FCPPT_LOG_WARNING(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("Didn't detect mouse warp motion! ")
			FCPPT_TEXT("Try to enable dga mouse instead.")
	);
}

void
sge::x11input::mouse::private_mouse_motion(
	mouse_coordinate_t const deltax,
	mouse_coordinate_t const deltay
)
{
	if(deltax)
		callback(
			input::key_pair(
				mouse_x,
				deltax
			)
		);

	if(deltay)
		callback(
			input::key_pair(
				mouse_y,
				deltay
			)
		);
}

namespace
{

sge::input::key_type
mouse_key(
	unsigned const x11code
)
{
	switch(x11code)
	{
	case 1:
		return sge::x11input::mouse_l;
	case 2:
		return sge::x11input::mouse_m;
	case 3:
		return sge::x11input::mouse_r;
	}
	
	return sge::x11input::undefined_mouse_key;
}

}
