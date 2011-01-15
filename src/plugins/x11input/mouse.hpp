/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "device/raw_event_fwd.hpp"
#include "device/window_event_fwd.hpp"
#include "device/parameters_fwd.hpp"
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_function.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_function.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace x11input
{

class mouse
:
	public sge::input::mouse::device
{
	FCPPT_NONCOPYABLE(
		mouse
	)
public:
	explicit mouse(
		x11input::device::parameters const &
	);

	~mouse();
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
		x11input::device::raw_event const &
	);

	void
	on_button_down(
		x11input::device::window_event const &
	);

	void
	on_button_up(
		x11input::device::window_event const &
	);

	void
	button_event(
		x11input::device::window_event const &,
		bool pressed
	);

	fcppt::signal::connection_manager const connections_;

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
