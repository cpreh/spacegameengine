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
#include "color.hpp"
#include "cursor.hpp"
#include "device.hpp"
#include "mouse_coordinate.hpp"
#include "mouse_pos.hpp"
#include "mouse_grab_fwd.hpp"
#include "pixmap.hpp"
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_function.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_function.hpp>
#include <awl/backends/x11/window/event/object_fwd.hpp>
#include <awl/backends/x11/window/event/processor_ptr.hpp>
#include <awl/backends/x11/window/event/signal/connection_manager.hpp>
#include <awl/backends/x11/window/instance_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
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
	mouse(
		awl::backends::x11::window::instance_ptr,
		awl::backends::x11::window::event::processor_ptr
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
		awl::backends::x11::window::event::object const &
	);

	void
	on_button_down(
		awl::backends::x11::window::event::object const &
	);

	void
	on_button_up(
		awl::backends::x11::window::event::object const &
	);

	void
	button_event(
		awl::backends::x11::window::event::object const &,
		bool pressed
	);

	void
	warped_motion(
		awl::backends::x11::window::event::object const &
	);

	void
	private_mouse_motion(
		mouse_coordinate deltax,
		mouse_coordinate deltay
	);

	awl::backends::x11::window::instance_ptr const window_;

	x11input::color const black_;

	x11input::pixmap const no_bmp_;

	x11input::cursor const cursor_;

	mouse_pos mouse_last_;

	awl::backends::x11::window::event::signal::connection_manager const connections_;

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
