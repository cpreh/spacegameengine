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
#ifdef USE_DGA
#include <X11/extensions/xf86dga.h>
#endif
#include <iostream>

sge::xinput::input_system::input_system(const x_window_ptr wnd)
 : wnd(wnd),
   mmap(XGetModifierMapping(wnd->display())),
   colormap(DefaultColormap(wnd->display(),wnd->screen())),
   mmwidth(mmap->max_keypermod),
   mouse_last(),
   _black(wnd->display(),colormap),
   _no_bmp(wnd->display()),
   _no_cursor(wnd->display()),
#ifdef USE_DGA
   dga_guard(wnd),
   use_dga(true)
#else
   use_dga(false)
#endif
{
#ifdef USE_DGA
	int flags;
	if(XF86DGAQueryDirectVideo(wnd->display(),wnd->screen(),&flags)==false)
		throw std::runtime_error("XF86DGAQueryDirectVideo() failed");
	if(flags & XF86DGADirectMouse)
	{
		std::cerr << "You compiled spacegameengine with use_dga=1 but DGA Mouse is not supported by your system! Disabling dga.";
		use_dga = false;
	}
#endif
	if(!use_dga)
	{
		Window root_return,
		       child_return;
		int root_x_return,
		    root_y_return,
		    win_x_return,
		    win_y_return;
		unsigned mask_return;

		XQueryPointer(wnd->display(), wnd->get_window(), &root_return, &child_return, &root_x_return, &root_y_return, &win_x_return, &win_y_return, &mask_return);
		mouse_last.x() = win_x_return;
		mouse_last.y() = win_y_return;
	}
	
	XColor black, dummy;
	if(XAllocNamedColor(wnd->display(), colormap, "black", &black, &dummy ) == 0)
		throw std::runtime_error("XAllocNamedColor() failed");
	_black.color = black;
	_black.dealloc = true;

	const char bm_no_data[] = { 0,0,0,0, 0,0,0,0 };
	_no_bmp.pixmap = XCreateBitmapFromData(wnd->display(), wnd->get_window(), bm_no_data, 8, 8);
	if(_no_bmp.pixmap == None)
		throw std::runtime_error("XCreateBitmapFromData() failed");
	_no_cursor.cursor = XCreatePixmapCursor(wnd->display(), _no_bmp.pixmap, _no_bmp.pixmap, &black, &black, 0, 0);
	if(_no_cursor.cursor == None)
		throw std::runtime_error("XCreatePixmapCursor() failed");

	grab();
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
	XUngrabKeyboard(wnd->display(),CurrentTime);
	XUngrabPointer(wnd->display(),CurrentTime);
}

boost::signals::connection sge::xinput::input_system::register_callback(const callback& c)
{
	return sig.connect(c);
}

void sge::xinput::input_system::grab()
{
	grab_pointer();
	grab_keyboard();
	XSync(wnd->display(), False);
}

void sge::xinput::input_system::grab_pointer()
{
	for(;;)
		if(handle_grab(XGrabPointer(wnd->display(), wnd->get_window(), True, PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, wnd->get_window(), _no_cursor.cursor, CurrentTime)))
			return;
}

void sge::xinput::input_system::grab_keyboard()
{
	for(;;)
		if(handle_grab(XGrabKeyboard(wnd->display(), wnd->get_window(), True, GrabModeAsync, GrabModeAsync, CurrentTime)))
			return;
}

bool sge::xinput::input_system::handle_grab(const int r) const
{
	switch(r) {
	case GrabSuccess:
		return true;
	case GrabFrozen:
		throw std::runtime_error("x11: Grab frozen!");
	case GrabNotViewable:
		throw std::runtime_error("x11: GrabNotViewable");
	case AlreadyGrabbed:
		break;
	case GrabInvalidTime:
		throw std::runtime_error("x11: GrabInvalidTime");
	}

	sleep(100);
	return false;
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
			// check for repeated key (thanks to SDL)
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
			
			sig(key_pair(key_type(get_key_name(ks), get_key_code(ks), static_cast<unsigned char>(code)), xev.type == KeyRelease ? 0 : 1));
			break;
			}
		case ButtonPress:
		case ButtonRelease:
			sig(key_pair(mouse_key(xev.xbutton.button), xev.type == ButtonRelease ? 0 : 1));
			break;
		case MotionNotify:
			if(use_dga)
				dga_motion(xev);
			else
				warped_motion(xev);
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

void sge::xinput::input_system::enable_dga(const bool 
#ifdef USE_DGA
		enable
#endif
)
{
#ifdef USE_DGA
	if(!use_dga)
		return;
	XF86DGADirectVideo(wnd->display(), wnd->screen(), enable ? XF86DGADirectMouse : 0);
	dga_guard.enabled = enable;
#endif
}

sge::key_type sge::xinput::input_system::mouse_key(const unsigned x11code) const
{
	switch(x11code) {
	case 1:
		return key_type("Mouse1",KC_MOUSEL,0);
	case 3:
		return key_type("Mouse2",KC_MOUSER,0);
	default:
		return key_type("Undefined mouse key",KC_None,0);
	}
}

std::string sge::xinput::input_system::get_key_name(const KeySym ks) const
{
	const char* const name = XKeysymToString(ks);
	return name ? name : "unknown";
}

sge::key_code sge::xinput::input_system::get_key_code(const KeySym ks) const
{
	x11_to_sge_array::const_iterator it = x11tosge.find(ks);
	if(it == x11tosge.end())
		return KC_None;
	return it->second;
}

/*void sge::xinput::input_system::update_modifiers(const key_value_array& keys)
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
}*/

void sge::xinput::input_system::private_mouse_motion(const mouse_coordinate_t deltax, const mouse_coordinate_t deltay)
{
	if(deltax)
		sig(key_pair(key_type("MouseX", KC_MOUSEX, 0), space_unit(deltax) / wnd->size().w));
	if(deltay)
		sig(key_pair(key_type("MouseY", KC_MOUSEY, 0), space_unit(deltay) / wnd->size().h));
}

void sge::xinput::input_system::dga_motion(XEvent& xevent)
{
	mouse_coordinate_t dx = xevent.xmotion.x_root,
	                   dy = xevent.xmotion.y_root;

	while(XCheckTypedEvent(wnd->display(), MotionNotify, &xevent))
	{
		dx += xevent.xmotion.x_root;
		dy += xevent.xmotion.y_root;
	}

	private_mouse_motion(dx, dy);
}

// thanks to SDL
void sge::xinput::input_system::warped_motion(XEvent& xevent)
{
	const mouse_coordinate_t MOUSE_FUDGE_FACTOR = 8;

	const mouse_coordinate_t w = wnd->width(),
	                         h = wnd->height();
	mouse_coordinate_t deltax = xevent.xmotion.x - mouse_last.x(),
	                   deltay = xevent.xmotion.y - mouse_last.y();
	
	mouse_last.x() = xevent.xmotion.x;
	mouse_last.y() = xevent.xmotion.y;

	private_mouse_motion(deltax, deltay);

	if ( !((xevent.xmotion.x < MOUSE_FUDGE_FACTOR) ||
	     (xevent.xmotion.x > (w-MOUSE_FUDGE_FACTOR)) ||
	     (xevent.xmotion.y < MOUSE_FUDGE_FACTOR) ||
	     (xevent.xmotion.y > (h-MOUSE_FUDGE_FACTOR)) ))
		return;
	
	while ( XCheckTypedEvent(wnd->display(), MotionNotify, &xevent) )
	{
		deltax = xevent.xmotion.x - mouse_last.x();
		deltay = xevent.xmotion.y - mouse_last.y();

		mouse_last.x() = xevent.xmotion.x;
		mouse_last.y() = xevent.xmotion.y;

		private_mouse_motion(deltax, deltay);
	}
	mouse_last.x() = w/2;
	mouse_last.y() = h/2;
	XWarpPointer(wnd->display(), None, wnd->get_window(), 0, 0, 0, 0, mouse_last.x(), mouse_last.y());

	const unsigned max_loops = 10;
	for(unsigned i = 0; i < max_loops; ++i )
	{
		XMaskEvent(wnd->display(), PointerMotionMask, &xevent);
		if ( (xevent.xmotion.x > mouse_last.x() - MOUSE_FUDGE_FACTOR) &&
		     (xevent.xmotion.x < mouse_last.x() + MOUSE_FUDGE_FACTOR) &&
		     (xevent.xmotion.y > mouse_last.y() - MOUSE_FUDGE_FACTOR) &&
		     (xevent.xmotion.y < mouse_last.y() + MOUSE_FUDGE_FACTOR) )
			break;

		if(i == max_loops - 1)
			std::cerr << "warning: didn't detect mouse warp motion! Try to enable dga mouse instead.\n";
	}
}
