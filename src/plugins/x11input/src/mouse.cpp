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
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unqiue_ptr.hpp>
#include <fcppt/text.hpp>

namespace
{

sge::input::mouse::button_code::type
mouse_key_code(
	unsigned x11code
);

}

sge::x11input::mouse::mouse(
	x11::window_ptr const _wnd
)
:
	wnd_(_wnd),
	black_(
		_wnd->display(),
		::XDefaultColormap(
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
	mouse_last_(
		x11input::get_pointer(
			_wnd
		)
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				wnd_->register_callback(
					MotionNotify,
					std::tr1::bind(
						&mouse::on_motion,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				wnd_->register_callback(
					ButtonPress,
					std::tr1::bind(
						&mouse::on_button_down,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				wnd_->register_callback(
					ButtonRelease,
					std::tr1::bind(
						&mouse::on_button_up,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	grab_(),
	button_signal_(),
	axis_signal_()
{
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
	grab_.take(
		fcppt::make_unique_ptr<
			x11input::mouse_grab
		>(
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
	XEvent const &_event
)
{
	warped_motion(
		_event
	);
}

void
sge::x11input::mouse::on_button_down(
	XEvent const &_event
)
{
	button_event(
		_event,
		true
	);
}

void
sge::x11input::mouse::on_button_up(
	XEvent const &_event
)
{
	button_event(
		_event,
		false
	);
}

void
sge::x11input::mouse::button_event(
	XEvent const &_event,
	bool const _pressed
)
{
	button_signal(
		input::mouse::button_event(
			::mouse_key_code(
				_event.xbutton.button
			),
			_pressed
		)
	);
}

void
sge::x11input::mouse::warped_motion(
	XEvent _event
)
{
	if(
		!grab_
	)
		return;

	mouse_coordinate const
		mouse_fudge_factor = 8,
		w = wnd_->size().w(),
		h = wnd_->size().h();

	mouse_coordinate
		deltax = _event.xmotion.x - mouse_last_.x(),
		deltay = _event.xmotion.y - mouse_last_.y();

	mouse_last_.x() = _event.xmotion.x;
	mouse_last_.y() = _event.xmotion.y;

	private_mouse_motion(
		deltax,
		deltay
	);

	if(
		!((_event.xmotion.x < mouse_fudge_factor) ||
		(_event.xmotion.x > (w-mouse_fudge_factor)) ||
		(_event.xmotion.y < mouse_fudge_factor) ||
		(_event.xmotion.y > (h-mouse_fudge_factor)) )
	)
		return;

	while(
		::XCheckTypedEvent(
			wnd_->display()->get(),
			MotionNotify,
			&_event
		)
	)
	{
		deltax = _event.xmotion.x - mouse_last_.x();
		deltay = _event.xmotion.y - mouse_last_.y();

		mouse_last_.x() = _event.xmotion.x;
		mouse_last_.y() = _event.xmotion.y;

		private_mouse_motion(
			deltax,
			deltay
		);
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
		::XMaskEvent(
			wnd_->display()->get(),
			PointerMotionMask,
			&xevent
		);

		if(
			(_event.xmotion.x > mouse_last_.x() - mouse_fudge_factor) &&
			(_event.xmotion.x < mouse_last_.x() + mouse_fudge_factor) &&
			(_event.xmotion.y > mouse_last_.y() - mouse_fudge_factor) &&
			(_event.xmotion.y < mouse_last_.y() + mouse_fudge_factor)
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
	mouse_coordinate const _deltax,
	mouse_coordinate const _deltay
)
{
	if(
		_deltax
	)
		axis_signal_(
			input::mouse::axis_event(
				input::mouse::axis::x
				deltax
			)
		);

	if(
		_deltay
	)
		axis_signal_(
			input::mouse::axis_event(
				input::mouse::axis::y,
				_deltay
			)
		);
}

namespace
{

sge::input::mouse::button_code::type
mouse_key_code(
	unsigned const _x11code
)
{
	switch(
		_x11code
	)
	{
	case 1:
		return sge::input::mouse::button::left;
	case 2:
		return sge::input::mouse::button::middle;
	case 3:
		return sge::input::mouse::button::right;
	}
	
	return sge::input::mouse::button::unknown;
}

}
