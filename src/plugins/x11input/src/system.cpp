/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <X11/Xlib.h>
#include <X11/X.h>
#ifdef SGE_USE_DGA
#include <X11/extensions/xf86dga.h>
#endif
#include "../system.hpp"
#include "../mouse.hpp"
#include "../translation.hpp"
#include "../device.hpp"
#include <sge/x11/display.hpp>
#include <sge/x11/window.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/log/headers.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/time/sleep.hpp>
#include <sge/time/millisecond.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <cstring>
#include <ostream>

sge::x11input::system::system(
	x11::window_ptr const wnd)
 :
	wnd(wnd),
	black_(
		wnd->display(),
		XDefaultColormap(
			wnd->display()->get(),
			wnd->screen()),
		SGE_TEXT("black")),
	no_bmp_(
		wnd->display(),
		wnd->get_window()),
	no_cursor_(
		wnd->display(),
		no_bmp_.get(),
		black_.get()),
#ifdef SGE_USE_DGA
	use_dga(true)
#else
	use_dga(false)
#endif
{
#ifdef SGE_USE_DGA
	int flags;
	if(XF86DGAQueryDirectVideo(wnd->display()->get(),wnd->screen(),&flags)==false)
		throw exception(
			SGE_TEXT("XF86DGAQueryDirectVideo() failed!"));

	if(flags & XF86DGADirectMouse)
	{
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT(
					"You compiled spacegameengine with use_dga=1 but DGA Mouse is not supported by your system!"
					"Maybe you are missing libXxf86dga or a proper video driver? Disabling dga."));
		use_dga = false;
	}
#endif

	connections.connect(wnd->register_callback(KeyPress, boost::bind(&system::on_key_event, this, _1)));
	connections.connect(wnd->register_callback(KeyRelease, boost::bind(&system::on_key_event, this, _1)));
	connections.connect(wnd->register_callback(EnterNotify, boost::bind(&system::on_acquire, this, _1)));
	connections.connect(wnd->register_callback(LeaveNotify, boost::bind(&system::on_release, this, _1)));
	connections.connect(wnd->register_callback(FocusIn, boost::bind(&system::on_acquire, this, _1)));
	connections.connect(wnd->register_callback(FocusOut, boost::bind(&system::on_release, this, _1)));
	connections.connect(wnd->register_callback(MapNotify, boost::bind(&system::on_acquire, this, _1)));
	connections.connect(wnd->register_callback(UnmapNotify, boost::bind(&system::on_release, this, _1)));

	typedef std::auto_ptr<
		device
	> device_auto_ptr;

	input::callback const callback(
		boost::bind(
			&system::emit_callback,
			this,
			_1));

	{
		device_auto_ptr mouse_(
			new mouse(
				wnd,
				no_cursor_,
				callback,
				use_dga));
		devices.push_back(mouse_);
	}
}

sge::x11input::system::~system()
{
	if(wnd->fullscreen())
		XUngrabKeyboard(wnd->display()->get(), CurrentTime);
	XUngrabPointer(wnd->display()->get(), CurrentTime);
}

sge::signals::connection const
sge::x11input::system::register_callback(
	input::callback const &c)
{
	return sig.connect(c);
}

sge::signals::connection const
sge::x11input::system::register_repeat_callback(
	input::repeat_callback const &c)
{
	return repeat_sig.connect(c);
}

void sge::x11input::system::dispatch()
{
}

sge::window_ptr const
sge::x11input::system::get_window() const
{
	return wnd;
}

void sge::x11input::system::emit_callback(
	input::key_pair const &k)
{
	sig(k);
}

void sge::x11input::system::grab()
{
	grab_pointer();
	if(wnd->fullscreen())
		grab_keyboard();
	wnd->display()->sync();
}

void sge::x11input::system::grab_pointer()
{
	for(;;)
		if(handle_grab(
			XGrabPointer(
				wnd->display()->get(),
				wnd->get_window(),
				True,
				PointerMotionMask
					| ButtonPressMask
					| ButtonReleaseMask,
				GrabModeAsync,
				GrabModeAsync,
				wnd->get_window(),
				no_cursor_.get(),
				CurrentTime)))
			return;
}

void sge::x11input::system::grab_keyboard()
{
	for(;;)
		if(handle_grab(
			XGrabKeyboard(
				wnd->display()->get(),
				wnd->get_window(),
				True,
				GrabModeAsync,
				GrabModeAsync,
				CurrentTime)))
			return;
}

bool sge::x11input::system::handle_grab(const int r) const
{
	switch(r) {
	case GrabSuccess:
		return true;
	case GrabFrozen:
		throw exception(SGE_TEXT("x11: Grab frozen!"));
	case GrabNotViewable:
	case AlreadyGrabbed:
		break;
	case GrabInvalidTime:
		throw exception(SGE_TEXT("x11: GrabInvalidTime!"));
	}

	time::sleep(
		time::millisecond(
			static_cast<time::unit>
				(1)));
	return false;
}

void sge::x11input::system::on_key_event(const XEvent& xev)
{
	// check for repeated key (thanks to SDL)
	if(xev.type == KeyRelease && XPending(wnd->display()->get()))
	{
		XEvent peek;
		XPeekEvent(wnd->display()->get(), &peek);
		if(peek.type == KeyPress &&
		   peek.xkey.keycode == xev.xkey.keycode &&
		   (peek.xkey.time - xev.xkey.time) < 2)
		{
			XNextEvent(wnd->display()->get(), &peek);
			repeat_sig(create_key_type(xev));
			return;
		}
	}

	sig(input::key_pair(create_key_type(xev), xev.type == KeyRelease ? 0 : 1));
}

sge::input::key_type sge::x11input::system::create_key_type(const XEvent& xev)
{
	XComposeStatus state;
	KeySym ks;
	boost::array<char,32> keybuf;

	const int num_chars = XLookupString(
		const_cast<XKeyEvent*>(reinterpret_cast<const XKeyEvent*>(&xev)),
		keybuf.c_array(),
		static_cast<int>(keybuf.size()),
		&ks,
		&state);
	const char code = keybuf[0];

	if(num_chars > 1)
	{
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("stub: character '")
				<< code
				<< SGE_TEXT("' in XLookupString has ")
				<< num_chars
				<< SGE_TEXT(" bytes!"));
		return input::key_type();
	}

	return input::key_type(get_key_name(ks), get_key_code(ks), code);
}

void sge::x11input::system::on_release(const XEvent&)
{
	XUngrabPointer(wnd->display()->get(), CurrentTime);
}

void sge::x11input::system::on_acquire(const XEvent&)
{
	grab();
}

sge::string const sge::x11input::system::get_key_name(const KeySym ks) const
{
	const char* const name = XKeysymToString(ks);
	return name ? input::key_type::string(name,name+std::strlen(name)) : SGE_TEXT("unknown");
}

sge::input::key_code sge::x11input::system::get_key_code(const KeySym ks) const
{
	return translate_key_code(ks);
}
