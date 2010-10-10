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


#include "../mouse.hpp"
#include "../get_pointer.hpp"
#include "../warp_pointer.hpp"
#include "../mouse_grab.hpp"
#include <X11/Xlib.h>
#include <sge/log/global.hpp>
#include <sge/input/key_code.hpp>
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

sge::input::key_code
mouse_key_code(
	unsigned x11code
);

}

sge::x11input::mouse::mouse(
	x11::window_ptr const _wnd,
	input::callback const &_callback
)
:
	wnd_(_wnd),
	black_(
		_wnd->display(),
		XDefaultColormap(
			_wnd->display()->get(),
			_wnd->screen()
		), // TODO: do we have to release this?
		FCPPT_TEXT("black")
	),
	no_bmp_(
		_wnd->display(),
		_wnd->get()
	),
	cursor_(
		_wnd->display(),
		no_bmp_.get(),
		black_.get()
	),
	callback_(_callback),
	mouse_last_(
		x11input::get_pointer(
			_wnd
		)
	),
	connections_(),
	grab_(),
	button_signal_(),
	axis_signal_()
{
	connections_.connect(
		wnd_->register_callback(
			MotionNotify,
			std::tr1::bind(
				&mouse::on_motion,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections_.connect(
		wnd_->register_callback(
			ButtonPress,
			std::tr1::bind(
				&mouse::on_button_down,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections_.connect(
		wnd_->register_callback(
			ButtonRelease,
			std::tr1::bind(
				&mouse::on_button_up,
				this,
				std::tr1::placeholders::_1
			)
		)
	);
}

sge::x11input::mouse::~mouse()
{
}

fcppt::signal::auto_connection
sge::x11input::mouse::button_callback(
	input::mouse::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::mouse::axis_callback(
	input::mouse::axis_callback const &_callback
)
{
	return
		axis_signal_.connect(
			_callback
		);
}

void
sge::x11input::mouse::grab()
{
	grab_.reset(
		new mouse_grab(
			wnd_,
			cursor_
		)
	);
}

void
sge::x11input::mouse::ungrab()
{
	grab_.reset();
}

void
sge::x11input::mouse::on_motion(
	XEvent const &e
)
{
	warped_motion(e);
}

void
sge::x11input::mouse::on_button_down(
	XEvent const &e
)
{
	callback_(
		input::key_pair(
			input::key_type(
				::mouse_key_code(
					e.xbutton.button
				)
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
	callback_(
		input::key_pair(
			input::key_type(
				::mouse_key_code(
					e.xbutton.button
				)
			),
			0
		)
	);
}

void
sge::x11input::mouse::warped_motion(
	XEvent xevent
)
{
	if(!grab_)
		return;

	mouse_coordinate const
		mouse_fudge_factor = 8,
		w = wnd_->size().w(),
		h = wnd_->size().h();

	mouse_coordinate
		deltax = xevent.xmotion.x - mouse_last_.x(),
		deltay = xevent.xmotion.y - mouse_last_.y();

	mouse_last_.x() = xevent.xmotion.x;
	mouse_last_.y() = xevent.xmotion.y;

	private_mouse_motion(
		deltax,
		deltay
	);

	if (
		!((xevent.xmotion.x < mouse_fudge_factor) ||
		(xevent.xmotion.x > (w-mouse_fudge_factor)) ||
		(xevent.xmotion.y < mouse_fudge_factor) ||
		(xevent.xmotion.y > (h-mouse_fudge_factor)) )
	)
		return;

	while(
		XCheckTypedEvent(
			wnd_->display()->get(),
			MotionNotify,
			&xevent
		)
	)
	{
		deltax = xevent.xmotion.x - mouse_last_.x();
		deltay = xevent.xmotion.y - mouse_last_.y();

		mouse_last_.x() = xevent.xmotion.x;
		mouse_last_.y() = xevent.xmotion.y;

		private_mouse_motion(deltax, deltay);
	}

	mouse_last_.x() = w / 2;
	mouse_last_.y() = h / 2;

	x11input::warp_pointer(
		wnd_,
		mouse_last_
	);

	for(
		unsigned i = 0;
		i < 10;
		++i
	)
	{
		XMaskEvent(
			wnd_->display()->get(),
			PointerMotionMask,
			&xevent
		);

		if (
			(xevent.xmotion.x > mouse_last_.x() - mouse_fudge_factor) &&
			(xevent.xmotion.x < mouse_last_.x() + mouse_fudge_factor) &&
			(xevent.xmotion.y > mouse_last_.y() - mouse_fudge_factor) &&
			(xevent.xmotion.y < mouse_last_.y() + mouse_fudge_factor)
		)
			return;
	}

	FCPPT_LOG_WARNING(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("Didn't detect mouse warp motion!")
	);
}

void
sge::x11input::mouse::private_mouse_motion(
	mouse_coordinate const deltax,
	mouse_coordinate const deltay
)
{
	if(deltax)
		callback_(
			input::key_pair(
				input::key_type(
					input::kc::mouse_x_axis
				),
				deltax
			)
		);

	if(deltay)
		callback_(
			input::key_pair(
				input::key_type(
					input::kc::mouse_y_axis
				),
				deltay
			)
		);
}

namespace
{

sge::input::key_code
mouse_key_code(
	unsigned const _x11code
)
{
	switch(
		_x11code
	)
	{
	case 1:
		return sge::input::kc::mouse_l;
	case 2:
		return sge::input::kc::mouse_m;
	case 3:
		return sge::input::kc::mouse_r;
	}
	
	return sge::input::kc::none;
}

}
