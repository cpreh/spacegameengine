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
#include "../input_system.hpp"
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/extensions/xf86dga.h>

sge::xinput::input_system::input_system(const x_window_ptr wnd)
	: wnd(wnd), mmap(XGetModifierMapping(wnd->get_display())), mmwidth(mmap->max_keypermod), last_mouse(0), dga_guard(wnd)
{
	int flags;
	if(XF86DGAQueryDirectVideo(wnd->get_display(),wnd->get_screen(),&flags)==false)
		throw std::runtime_error("XF86DGAQueryDirectVideo() failed");
//	if(!(flags & XF86DGADirectMouse))
//		throw std::runtime_error("DGA Mouse not supported! Non DGA implementation is not present yet!");

	XF86DGADirectVideo(wnd->get_display(),wnd->get_screen(),XF86DGADirectMouse);
	dga_guard.enabled = true;

	if(XGrabPointer(wnd->get_display(),wnd->get_window(),true,None,/*PointerMotionMask|KeyPressMask|KeyReleaseMask,*/GrabModeAsync,GrabModeAsync,wnd->get_window(),None,CurrentTime) != GrabSuccess)
		throw std::runtime_error("XGrabPointer() failed");
	if(XGrabKeyboard(wnd->get_display(),wnd->get_window(),true,GrabModeAsync, GrabModeAsync, CurrentTime) != GrabSuccess)
		throw std::runtime_error("XGrabKeyboard() failed");
	
	XDefineCursor(wnd->get_display(),wnd->get_window(),None);
	
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
	XUngrabKeyboard(wnd->get_display(),CurrentTime);
	XUngrabPointer(wnd->get_display(),CurrentTime);
}

sge::callback_handle sge::xinput::input_system::register_callback(const callback& c)
{
	return callback_handle(new callback_handle_impl(sig.connect(c)));
}

void sge::xinput::input_system::dispatch()
{
	XEvent xev;
	while(XCheckMaskEvent(wnd->get_display(), KeyReleaseMask | KeyPressMask, &xev))
	{
		XComposeStatus state;
		char keybuf[32];
		KeySym ks;
		const char ch = XLookupString(reinterpret_cast<XKeyEvent*>(&xev),keybuf,sizeof(keybuf),&ks,&state) == 1 ? keybuf[0] : 0;
		const key_type key(get_key_name(ks),modifiers,get_key_code(ks),ch);
		sig(key_pair(key, xev.type == KeyRelease ? 0 : 1));
	}
	
	Window root, child;
	int root_x, root_y, win_x, win_y;
	unsigned mask;
	XQueryPointer(wnd->get_display(),wnd->get_window(),&root,&child,&root_x,&root_y,&win_x,&win_y,&mask);
	const unsigned diff_mask = mask ^ last_mouse;
	if(diff_mask & Button1Mask)
		sig(key_pair(key_type("Mouse1",modifiers,KC_MOUSEL,0),mask & Button1Mask ? 1 : 0 ));
	if(diff_mask & Button2Mask)
		sig(key_pair(key_type("Mouse2",modifiers,KC_MOUSER,0),mask & Button2Mask ? 1 : 0));
	last_mouse = mask;

	int deltax = 0, deltay = 0;
	while(XCheckTypedEvent(wnd->get_display(), MotionNotify, &xev)) {
		deltax += xev.xmotion.x_root;
		deltay += xev.xmotion.y_root;
	}
	if(deltax)
		sig(key_pair(key_type("MouseX",modifiers,KC_MOUSEX,0),space_unit(deltax) / wnd->size().w));
	if(deltay)
		sig(key_pair(key_type("MouseY",modifiers,KC_MOUSEY,0),space_unit(deltay) / wnd->size().h));
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
