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


#ifndef SGE_X11INPUT_MOUSE_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_HPP_INCLUDED

#include "device.hpp"
#include "mouse_coordinate.hpp"
#include "dga.hpp"
#include <X11/Xlib.h>
#include <sge/input/callback.hpp>
#include <sge/signal/connection_manager.hpp>
#include <sge/x11/window_fwd.hpp>
#include <sge/x11/color.hpp>
#include <sge/x11/pixmap.hpp>
#include <sge/x11/cursor.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/scoped_ptr.hpp>

namespace sge
{
namespace x11
{
class cursor;
}

namespace x11input
{

class mouse_grab;

class mouse : public device {
public:
	mouse(
		x11::window_ptr,
		input::callback const &);
	~mouse();
private:
	void grab();
	void ungrab();

	void on_motion(
		XEvent const &);
	void on_button_down(
		XEvent const &);
	void on_button_up(
		XEvent const &);

	void dga_motion(XEvent);
	void warped_motion(XEvent);
	void private_mouse_motion(
		mouse_coordinate_t deltax,
		mouse_coordinate_t deltay);

	x11::window_ptr const wnd;
	x11::color      const black_;
	x11::pixmap     const no_bmp_;
	x11::cursor     const cur;
	input::callback const callback;
	mouse_pos             mouse_last;
	dga                   dga_;

	signal::connection_manager connections;

	scoped_ptr<
		mouse_grab
	> grab_;
};

}
}

#endif
