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


#include <X11/Xlib.h>
#include <sge/x11/display.hpp>
#include <sge/x11/window.hpp>
#include <sge/x11/sentry.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include "../pointer.hpp"

sge::x11input::mouse_pos const
sge::x11input::get_pointer(
        x11::window_ptr const wnd)
{
	Window root_return,
	       child_return;
	int root_x_return,
	    root_y_return,
	    win_x_return,
	    win_y_return;
	unsigned mask_return;

	SGE_X11_SENTRY

	XQueryPointer(
		wnd->display()->get(),
		wnd->get(),
		&root_return,
		&child_return,
		&root_x_return,
		&root_y_return,
		&win_x_return,
		&win_y_return,
		&mask_return);

	return mouse_pos(
		win_x_return,
		win_y_return);
}

void sge::x11input::warp_pointer(
	x11::window_ptr const wnd,
	mouse_pos const &pos)
{
	SGE_X11_SENTRY

	XWarpPointer(
		wnd->display()->get(),
		None,
		wnd->get(),
		0,
		0,
		0,
		0,
		pos.x(),
		pos.y());
}
