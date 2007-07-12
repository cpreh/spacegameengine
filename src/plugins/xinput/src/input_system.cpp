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


#include <boost/array.hpp>
#include <boost/bind.hpp>
#include "../../../input/key_type.hpp"
#include "../../../util.hpp"
#include "../../../iconv.hpp"
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
   colormap(DefaultColormap(wnd->display(), wnd->screen())),
   mouse_last(),
   _black(wnd->display(), colormap),
   _no_bmp(wnd->display(), wnd->get_window()),
   _no_cursor(wnd->display(), _no_bmp.pixmap(), _black.color()),
#ifdef USE_DGA
   _dga_guard(wnd->display(), wnd->screen()),
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
		std::cerr << "You compiled spacegameengine with use_dga=1 but DGA Mouse is not supported by your system! Maybe you are missing libXxf86dga or a proper video driver? Disabling dga.";
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
	
	wnd->register_callback(KeyPress, boost::bind(&input_system::on_key_event, this, _1));
	wnd->register_callback(KeyRelease, boost::bind(&input_system::on_key_event, this, _1));
	wnd->register_callback(ButtonPress, boost::bind(&input_system::on_button_event, this, _1));
	wnd->register_callback(ButtonRelease, boost::bind(&input_system::on_button_event, this, _1));
	wnd->register_callback(MotionNotify, boost::bind(&input_system::on_motion_event, this, _1));
	wnd->register_callback(EnterNotify, boost::bind(&input_system::on_acquire, this, _1));
	wnd->register_callback(LeaveNotify, boost::bind(&input_system::on_release, this, _1));
	wnd->register_callback(FocusIn, boost::bind(&input_system::on_acquire, this, _1));
	wnd->register_callback(FocusOut, boost::bind(&input_system::on_release, this, _1));
	wnd->register_callback(MapNotify, boost::bind(&input_system::on_acquire, this, _1));
	wnd->register_callback(UnmapNotify, boost::bind(&input_system::on_release, this, _1));

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
	//XK_Prior
	x11tosge[XK_Page_Up] = KC_PGUP;
	//XK_Next
	x11tosge[XK_Page_Down] = KC_PGDN;
	x11tosge[XK_End] = KC_END;
	x11tosge[XK_Begin] = KC_HOME;

//	x11tosge[XK_KP_Space];
//	x11tosge[XK_KP_Tab];
//	x11tosge[XK_KP_Enter] = KC_ENTER;
/*	x11tosge[XK_KP_F1];
	x11tosge[XK_KP_F2];
	x11tosge[XK_KP_F3];
	x11tosge[XK_KP_F4];
	x11tosge[XK_KP_Home] = KC_NUM_HOME;
	x11tosge[XK_KP_Left] = KC_NUM_LEFT;
	x11tosge[XK_KP_Up] = KC_NUM_UP;
#define XK_KP_Right                      0xff98
#define XK_KP_Down                       0xff99
#define XK_KP_Prior                      0xff9a
#define XK_KP_Page_Up                    0xff9a
#define XK_KP_Next                       0xff9b
#define XK_KP_Page_Down                  0xff9b
#define XK_KP_End                        0xff9c
#define XK_KP_Begin                      0xff9d
#define XK_KP_Insert                     0xff9e
#define XK_KP_Delete                     0xff9f
#define XK_KP_Equal                      0xffbd/
#define XK_KP_Multiply                   0xffaa
#define XK_KP_Add                        0xffab
#define XK_KP_Separator                  0xffac
#define XK_KP_Subtract                   0xffad
#define XK_KP_Decimal                    0xffae
#define XK_KP_Divide                     0xffaf

#define XK_KP_0                          0xffb0
#define XK_KP_1                          0xffb1
#define XK_KP_2                          0xffb2
#define XK_KP_3                          0xffb3
#define XK_KP_4                          0xffb4
#define XK_KP_5                          0xffb5
#define XK_KP_6                          0xffb6
#define XK_KP_7                          0xffb7
#define XK_KP_8                          0xffb8
#define XK_KP_9                          0xffb9*/

	x11tosge[XK_F1] = KC_F1;
	x11tosge[XK_F2] = KC_F2;
	x11tosge[XK_F3] = KC_F3;
	x11tosge[XK_F4] = KC_F4;
	x11tosge[XK_F5] = KC_F5;
	x11tosge[XK_F6] = KC_F6;
	x11tosge[XK_F7] = KC_F7;
	x11tosge[XK_F8] = KC_F8;
	x11tosge[XK_F9] = KC_F9;
	x11tosge[XK_F10] = KC_F10;
	x11tosge[XK_F11] = KC_F11;
	x11tosge[XK_F12] = KC_F12;
//#define XK_L1                            0xffc8
/*
#define XK_L2                            0xffc9
#define XK_F13                           0xffca
#define XK_L3                            0xffca
#define XK_F14                           0xffcb
#define XK_L4                            0xffcb
#define XK_F15                           0xffcc
#define XK_L5                            0xffcc
#define XK_F16                           0xffcd
#define XK_L6                            0xffcd
#define XK_F17                           0xffce
#define XK_L7                            0xffce
#define XK_F18                           0xffcf
#define XK_L8                            0xffcf
#define XK_F19                           0xffd0
#define XK_L9                            0xffd0
#define XK_F20                           0xffd1
#define XK_L10                           0xffd1
#define XK_F21                           0xffd2
#define XK_R1                            0xffd2
#define XK_F22                           0xffd3
#define XK_R2                            0xffd3
#define XK_F23                           0xffd4
#define XK_R3                            0xffd4
#define XK_F24                           0xffd5
#define XK_R4                            0xffd5
#define XK_F25                           0xffd6
#define XK_R5                            0xffd6
#define XK_F26                           0xffd7
#define XK_R6                            0xffd7
#define XK_F27                           0xffd8
#define XK_R7                            0xffd8
#define XK_F28                           0xffd9
#define XK_R8                            0xffd9
#define XK_F29                           0xffda
#define XK_R9                            0xffda
#define XK_F30                           0xffdb
#define XK_R10                           0xffdb
#define XK_F31                           0xffdc
#define XK_R11                           0xffdc
#define XK_F32                           0xffdd
#define XK_R12                           0xffdd
#define XK_F33                           0xffde
#define XK_R13                           0xffde
#define XK_F34                           0xffdf
#define XK_R14                           0xffdf
#define XK_F35                           0xffe0
#define XK_R15                           0xffe0
*/


	x11tosge[XK_Shift_L] = KC_LSHIFT;
	x11tosge[XK_Shift_R] = KC_RSHIFT;
	x11tosge[XK_Control_L] = KC_LCTRL;
	x11tosge[XK_Control_R] = KC_RCTRL;
	//XK_Caps_Lock
	x11tosge[XK_Shift_Lock] = KC_LSHIFT; // ???

//#define XK_Meta_L                        0xffe7  /* Left meta */
//#define XK_Meta_R                        0xffe8  /* Right meta */
//#define XK_Alt_L                         0xffe9  /* Left alt */
//#define XK_Alt_R                         0xffea  /* Right alt */
//#define XK_Super_L                       0xffeb  /* Left super */
//#define XK_Super_R                       0xffec  /* Right super */
//#define XK_Hyper_L                       0xffed  /* Left hyper */
//#define XK_Hyper_R                       0xffee  /* Right hyper */
}

sge::xinput::input_system::~input_system()
{
	if(wnd->fullscreen())
		XUngrabKeyboard(wnd->display(),CurrentTime);
	XUngrabPointer(wnd->display(),CurrentTime);
}

boost::signals::connection sge::xinput::input_system::register_callback(const callback& c)
{
	return sig.connect(c);
}

boost::signals::connection sge::xinput::input_system::register_repeat_callback(const repeat_callback& c)
{
	return repeat_sig.connect(c);
}

void sge::xinput::input_system::dispatch()
{
}

void sge::xinput::input_system::grab()
{
	grab_pointer();
	if(wnd->fullscreen())
		grab_keyboard();
	XSync(wnd->display(), False);
}

void sge::xinput::input_system::grab_pointer()
{
	for(;;)
		if(handle_grab(XGrabPointer(wnd->display(), wnd->get_window(), True, PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, wnd->get_window(), _no_cursor.cursor(), CurrentTime)))
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
	case AlreadyGrabbed:
		break;
	case GrabInvalidTime:
		throw std::runtime_error("x11: GrabInvalidTime");
	}

	sleep(100);
	return false;
}

void sge::xinput::input_system::on_motion_event(const XEvent& xev)
{
	if(use_dga)
		dga_motion(xev);
	else
		warped_motion(xev);
}

void sge::xinput::input_system::on_key_event(const XEvent& xev)
{
	// check for repeated key (thanks to SDL)
	if(xev.type == KeyRelease
	   && xev.type == KeyRelease && XPending(wnd->display()))
	{
		XEvent peek;
		XPeekEvent(wnd->display(), &peek);
		if(peek.type == KeyPress &&
		   peek.xkey.keycode == xev.xkey.keycode &&
		   (peek.xkey.time - xev.xkey.time) < 2)
		{
			XNextEvent(wnd->display(), &peek);
			repeat_sig(create_key_type(xev));
			return;
		}
	}
	
	sig(key_pair(create_key_type(xev), xev.type == KeyRelease ? 0 : 1));
}

sge::key_type sge::xinput::input_system::create_key_type(const XEvent& xev)
{
	XComposeStatus state;
	KeySym ks;
	boost::array<char,32> keybuf;

	const int num_chars = XLookupString(const_cast<XKeyEvent*>(reinterpret_cast<const XKeyEvent*>(&xev)), keybuf.c_array(), keybuf.size(), &ks, &state);
	const char code = keybuf[0];

	if(num_chars > 1)
	{
		std::cerr << "stub: character '" << code << "' in XLookupString has " << num_chars << " bytes!\n";
		return key_type();
	}

	return key_type(get_key_name(ks), get_key_code(ks), code);
}

void sge::xinput::input_system::on_button_event(const XEvent& xev)
{
	sig(key_pair(mouse_key(xev.xbutton.button), xev.type == ButtonRelease ? 0 : 1));
}

void sge::xinput::input_system::on_release(const XEvent&)
{
	enable_dga(false);
	XUngrabPointer(wnd->display(), CurrentTime);
}

void sge::xinput::input_system::on_acquire(const XEvent&)
{
	grab();
	enable_dga(true);
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
	_dga_guard.enable(enable);
#endif
}

sge::key_type sge::xinput::input_system::mouse_key(const unsigned x11code) const
{
	switch(x11code) {
	case 1:
		return mouse1;
	case 3:
		return mouse2;
	default:
		return undefined_mouse_key;
	}
}

sge::string sge::xinput::input_system::get_key_name(const KeySym ks) const
{
	const char* const name = XKeysymToString(ks);
	return name ? iconv(name) : iconv("unknown");
}

sge::key_code sge::xinput::input_system::get_key_code(const KeySym ks) const
{
	const x11_to_sge_array::const_iterator it = x11tosge.find(ks);
	if(it == x11tosge.end())
		return KC_None;
	return it->second;
}

void sge::xinput::input_system::private_mouse_motion(const mouse_coordinate_t deltax, const mouse_coordinate_t deltay)
{
	if(deltax)
		sig(key_pair(mouse_x, space_unit(deltax) / wnd->width()));
	if(deltay)
		sig(key_pair(mouse_y, space_unit(deltay) / wnd->height()));
}

void sge::xinput::input_system::dga_motion(XEvent xevent)
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
void sge::xinput::input_system::warped_motion(XEvent xevent)
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

const sge::key_type sge::xinput::input_system::mouse_x(sge::iconv("mouse_x"), KC_MOUSEX);
const sge::key_type sge::xinput::input_system::mouse_y(sge::iconv("mouse_y"), KC_MOUSEY);
const sge::key_type sge::xinput::input_system::undefined_mouse_key(sge::iconv("undefined mouse key"));
const sge::key_type sge::xinput::input_system::mouse1(sge::iconv("mouse_L"), KC_MOUSEL);
const sge::key_type sge::xinput::input_system::mouse2(sge::iconv("mouse_R"), KC_MOUSER);
