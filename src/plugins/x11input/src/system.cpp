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


#include <boost/foreach.hpp> // some header breaks BOOST_FOREACH
#include <X11/Xlib.h>
#include "../system.hpp"
#include "../mouse.hpp"
#include "../keyboard.hpp"
#include "../device.hpp"
#include <sge/x11/display.hpp>
#include <sge/x11/window.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/global.hpp>
#include <fcppt/text.hpp>
#include <sge/auto_ptr.hpp>
#include <tr1/functional>
#include <ostream>

sge::x11input::system::system(
	x11::window_ptr const wnd
)
:
	wnd(wnd),
	acquired(false)
{
	/*
	connections.connect(
		wnd->register_callback(
			EnterNotify,
			std::tr1::bind(
				&system::on_acquire,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections.connect(
		wnd->register_callback(
			LeaveNotify,
			std::tr1::bind(
				&system::on_release,
				this,
				std::tr1::placeholders::_1
			)
		)
	);
*/
	connections.connect(
		wnd->register_callback(
			FocusIn,
			std::tr1::bind(
				&system::on_acquire,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections.connect(
		wnd->register_callback(
			FocusOut,
			std::tr1::bind(
				&system::on_release,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections.connect(
		wnd->register_callback(
			MapNotify,
			std::tr1::bind(
				&system::on_acquire,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections.connect(
		wnd->register_callback(
			UnmapNotify,
			std::tr1::bind(
				&system::on_release,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	typedef auto_ptr<
		device
	> device_auto_ptr;

	input::callback const callback(
		std::tr1::bind(
			&system::emit_callback,
			this,
			std::tr1::placeholders::_1
		)
	);

	{
		device_auto_ptr mouse_(
			new mouse(
				wnd,
				callback
			)
		);

		devices.push_back(mouse_);
	}

	{
		device_auto_ptr keyboard_(
			new keyboard(
				wnd,
				callback,
				std::tr1::bind(
					&system::emit_repeat_callback,
					this,
					std::tr1::placeholders::_1
				)
			)
		);

		devices.push_back(keyboard_);
	}
}

sge::signal::auto_connection
sge::x11input::system::register_callback(
	input::callback const &c)
{
	return sig.connect(c);
}

sge::signal::auto_connection
sge::x11input::system::register_repeat_callback(
	input::repeat_callback const &c)
{
	return repeat_sig.connect(c);
}

void sge::x11input::system::dispatch()
{
}

sge::window::instance_ptr const
sge::x11input::system::window() const
{
	return wnd;
}

void sge::x11input::system::emit_callback(
	input::key_pair const &k)
{
	sig(k);
}

void sge::x11input::system::emit_repeat_callback(
	input::key_type const &k)
{
	repeat_sig(k);
}

void sge::x11input::system::on_acquire(
	XEvent const &)
{
	if(acquired)
		return;
	acquired = true;

	FCPPT_LOG_DEBUG(
		log::global(),
		log::_
			<< FCPPT_TEXT("x11: acquire window"));

	BOOST_FOREACH(device_vector::reference dev, devices)
		dev.grab();

	wnd->display()->sync();
}

void sge::x11input::system::on_release(
	XEvent const &)
{
	if(!acquired)
		return;
	acquired = false;

	FCPPT_LOG_DEBUG(
		log::global(),
		log::_
			<< FCPPT_TEXT("x11: release window"));

	BOOST_FOREACH(device_vector::reference dev, devices)
		dev.ungrab();
}
