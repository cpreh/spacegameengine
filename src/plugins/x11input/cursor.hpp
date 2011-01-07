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


#ifndef SGE_X11INPUT_CURSOR_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_HPP_INCLUDED

#include "cursor_fwd.hpp"
#include "cursor_confine_fwd.hpp"
#include "device/id.hpp"
#include "device/parameters_fwd.hpp"
#include "device/window_event_fwd.hpp"
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_function.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_function.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/window_mode.hpp>
#include <awl/backends/x11/window/instance_ptr.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace x11input
{

class cursor
:
	public sge::input::cursor::object
{
	FCPPT_NONCOPYABLE(
		cursor
	)
public:
	explicit cursor(
		x11input::device::parameters const &
	);

	~cursor();
private:
	fcppt::signal::auto_connection
	button_callback(
		input::cursor::button_callback const &
	);

	fcppt::signal::auto_connection
	move_callback(
		input::cursor::move_callback const &
	);

	input::cursor::position const
	position() const;

	void
	show();

	void
	hide();

	void
	window_mode(
		input::cursor::window_mode::type
	);

	void
	on_motion(
		x11input::device::window_event const &
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

	device::id const device_id_;

	awl::backends::x11::window::instance_ptr const window_;

	fcppt::signal::connection_manager const connections_;

	sge::input::cursor::position position_;

	fcppt::signal::object<
		sge::input::cursor::button_function
	> button_signal_;

	fcppt::signal::object<
		sge::input::cursor::move_function
	> move_signal_;

	fcppt::scoped_ptr<
		x11input::cursor_confine
	> cursor_confine_;
};

}
}

#endif
