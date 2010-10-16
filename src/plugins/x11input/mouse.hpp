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


#ifndef SGE_X11INPUT_MOUSE_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_HPP_INCLUDED

#include "mouse_fwd.hpp"
#include "device.hpp"
#include "mouse_coordinate.hpp"
#include "mouse_pos.hpp"
#include "mouse_grab_fwd.hpp"
#include <X11/Xlib.h>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_function.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_function.hpp>
#include <sge/x11/window_ptr.hpp>
#include <sge/x11/color.hpp>
#include <sge/x11/pixmap.hpp>
#include <sge/x11/cursor.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace x11input
{

class mouse
:
	public sge::input::mouse::device,
	public x11input::device
{
	FCPPT_NONCOPYABLE(
		mouse
	)
public:
	explicit mouse(
		x11::window_ptr
	);

	~mouse();

	void
	grab();

	void
	ungrab();
private:
	fcppt::signal::auto_connection
	button_callback(
		input::mouse::button_callback const &
	);

	fcppt::signal::auto_connection
	axis_callback(
		input::mouse::axis_callback const &
	);

	void
	on_motion(
		XEvent const &
	);

	void
	on_button_down(
		XEvent const &
	);

	void
	on_button_up(
		XEvent const &
	);

	void
	button_event(
		XEvent const &,
		bool pressed
	);

	void
	warped_motion(
		XEvent
	);

	void
	private_mouse_motion(
		mouse_coordinate deltax,
		mouse_coordinate deltay
	);

	x11::window_ptr const wnd_;

	x11::color const black_;

	x11::pixmap const no_bmp_;

	x11::cursor const cursor_;

	mouse_pos mouse_last_;

	fcppt::signal::connection_manager const connections_;

	fcppt::scoped_ptr<
		mouse_grab
	> grab_;

	fcppt::signal::object<
		sge::input::mouse::button_function
	> button_signal_;

	fcppt::signal::object<
		sge::input::mouse::axis_function
	> axis_signal_;
};

}
}

#endif
