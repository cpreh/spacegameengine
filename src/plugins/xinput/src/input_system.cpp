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


#include <cstddef>
#include "../../../bit.hpp"
#include "../../../input/key_type.hpp"
#include "../../../input/callback_handle.hpp"
#include "../../../util.hpp"
#include "../input_system.hpp"
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/extensions/xf86dga.h>
#include <iostream>
#include <signal.h>

void unset_dga_handler(int)
{
	Display* dsp = XOpenDisplay(NULL);
	if(!dsp)
		return;
	XF86DGADirectVideo(dsp, DefaultScreen(dsp), 0);
	XCloseDisplay(dsp);
}

sge::xinput::input_system::input_system(const x_window_ptr wnd)
	: wnd(wnd), mmap(XGetModifierMapping(wnd->display())), colormap(DefaultColormap(wnd->display(),wnd->screen())), mmwidth(mmap->max_keypermod), last_mouse(0), _black(wnd->display(),colormap), _no_bmp(wnd->display()), _no_cursor(wnd->display()), dga_guard(wnd)
{
	int flags;
	if(XF86DGAQueryDirectVideo(wnd->display(),wnd->screen(),&flags)==false)
		throw std::runtime_error("XF86DGAQueryDirectVideo() failed");
	if(flags & XF86DGADirectMouse)
		throw std::runtime_error("DGA Mouse not supported! Non DGA implementation is not present yet!");

	XColor black, dummy;
	if(XAllocNamedColor(wnd->display(), colormap, "black", &black, &dummy ) == 0)
		throw std::runtime_error("XAllocNamedColor() failed");
	_black.color = black;
	_black.dealloc = true;

	const char bm_no_data[] = { 0,0,0,0, 0,0,0,0 };
	_no_bmp.pixmap = XCreateBitmapFromData(wnd->display(), wnd->get_window(), bm_no_data, 8, 8 );
	if(_no_bmp.pixmap == None)
		throw std::runtime_error("XCreateBitmapFromData() failed");
	_no_cursor.cursor = XCreatePixmapCursor(wnd->display(), _no_bmp.pixmap, _no_bmp.pixmap, &black, &black, 0, 0);
	if(_no_cursor.cursor == None)
		throw std::runtime_error("XCreatePixmapCursor() failed");

	grab();
//	signal(SIGABRT,unset_dga_handler);
//	if(signal(SIGSEGV,unset_dga_handler) == SIG_ERR)
//		std::cerr << "Warning: Failed to set signal handler!\n";
	enable_dga(true);

	x11tosge[NoSymbol] = KC_None;
	x11tosge[XK_BackSpace] = KC_BACK;
	x11tosge[XK_Tab] = KC_TAB;
	x11tosge[XK_Return] = KC_RETURN;
	x11tosge[XK_Pause] = KC_PAUSE;
	x11tosge[XK_Scroll_Lock] = KC_SCROLL;
	x11tosge[XK_Escape] = KC_ESC;
	x11tosge[XK_Delete] = KC_DEL;

	x11tosge[XK_Home] = KC_HOME;
	x11tosge[XK_Left] = KC_LEFT;
	x11tosge[XK_Up]   = KC_UP;
	x11tosge[XK_Right] = KC_RIGHT;
	x11tosge[XK_Down] = KC_DOWN;
	//XK_Prior                0xFF55  /* Prior, previous */
	x11tosge[XK_Page_Up] = KC_PGUP;
	//XK_Next                 0xFF56  /* Next */
	x11tosge[XK_Page_Down] = KC_PGDN;
	x11tosge[XK_End] = KC_END;
	x11tosge[XK_Begin] = KC_HOME;
}

sge::xinput::input_system::~input_system()
{
	XUngrabPointer(wnd->display(),CurrentTime);
}

boost::signals::connection sge::xinput::input_system::register_callback(const callback& c)
{
	return sig.connect(c);
}

void sge::xinput::input_system::grab()
{
	for(;;)
	{
		const int r = XGrabPointer(wnd->display(), wnd->get_window(), True, PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, wnd->get_window(), _no_cursor.cursor, CurrentTime);
		switch(r) {
		case GrabSuccess:
			return;
		case GrabFrozen:
			throw std::runtime_error("x11: Grab frozen!");
		case GrabNotViewable:
			throw std::runtime_error("x11: GrabNotViewable");
		case AlreadyGrabbed:
			break;
		case GrabInvalidTime:
			throw std::runtime_error("x11: GrabInvalidTime");
		}
		sleep(10);
	}
}

void sge::xinput::input_system::dispatch()
{
	XEvent xev;
	while(XPending(wnd->display()))
	{
		XNextEvent(wnd->display(),&xev);
		if(XFilterEvent(&xev,None))
			continue;

		switch(xev.type) {
		case KeyPress:
		case KeyRelease:
			// check for repeated key
			if(xev.type == KeyRelease && XPending(wnd->display()))
			{
				XEvent peek;
				XPeekEvent(wnd->display(), &peek);
				if(peek.type == KeyPress &&
				   peek.xkey.keycode == xev.xkey.keycode)
				{
					XNextEvent(wnd->display(), &peek);
					continue;
				}
			}

			{
			XComposeStatus state;
			KeySym ks;
			char keybuf[32];

			const int num_chars = XLookupString(reinterpret_cast<XKeyEvent*>(&xev),keybuf,sizeof(keybuf),&ks,&state);
			const char code = keybuf[0];

			if(num_chars > 1)
			{
				std::cerr << "stub: character '" << keybuf << "' in XLookupString has " << num_chars << " bytes!\n";
				continue;
			}
			
			sig(key_pair(key_type(get_key_name(ks), modifiers, get_key_code(ks), static_cast<unsigned char>(code)), xev.type == KeyRelease ? 0 : 1));
			break;
			}
		case ButtonPress:
		case ButtonRelease:
			sig(key_pair(mouse_key(xev.xbutton.button), xev.type == ButtonRelease ? 0 : 1));
			break;
		case MotionNotify:
			if(xev.xmotion.x_root)
				sig(key_pair(key_type("MouseX", modifiers, KC_MOUSEX, 0), space_unit(xev.xmotion.x_root) / wnd->size().w));
			if(xev.xmotion.y_root)
				sig(key_pair(key_type("MouseY", modifiers, KC_MOUSEY, 0), space_unit(xev.xmotion.y_root) / wnd->size().h));
			break;
		case LeaveNotify:
			enable_dga(false);
			break;
		case EnterNotify:
			enable_dga(true);
			break;
		case MapNotify:
			grab();
			break;
		}
	}
}

void sge::xinput::input_system::enable_dga(const bool enable)
{
	XF86DGADirectVideo(wnd->display(), wnd->screen(), enable ? XF86DGADirectMouse : 0);
	dga_guard.enabled = enable;
}

sge::key_type sge::xinput::input_system::mouse_key(const unsigned x11code) const
{
	switch(x11code) {
	case 1:
		return key_type("Mouse1",modifiers,KC_MOUSEL,0);
	case 3:
		return key_type("Mouse2",modifiers,KC_MOUSER,0);
	default:
		return key_type("Undefined mouse key",modifiers,KC_None,0);
	}
}

std::string sge::xinput::input_system::get_key_name(const KeySym ks) const
{
	return XKeysymToString(ks);
}

sge::key_code sge::xinput::input_system::get_key_code(const KeySym ks) const
{
	x11_to_sge_array::const_iterator it = x11tosge.find(ks);
	if(it == x11tosge.end())
		return KC_None;
	return it->second;
}

// FIXME: modifiers should be updated
void sge::xinput::input_system::update_modifiers(const key_value_array& keys)
{
	for (unsigned i = 0; i < mmwidth; ++i)
	{
		KeyCode code;
		code = mmap->modifiermap[ControlMapIndex*mmwidth + i];
		if(code)
			modifiers.ctrl_down = bit_a(keys,code);

		code = mmap->modifiermap[ShiftMapIndex*mmwidth + i];
		if(code)
			modifiers.shift_down = bit_a(keys,code);

//		code = mmap->modifiermap[LockMapIndex*width + i];
//		if(code && 0!=bit(keys, code))
//			{return LOCK_DOWN;}
  	}
}
