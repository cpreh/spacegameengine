/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_X11INPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_signal.hpp>
#include <sge/x11input/cursor/entered.hpp>
#include <sge/x11input/cursor/grab_fwd.hpp>
#include <sge/x11input/cursor/object_fwd.hpp>
#include <sge/x11input/cursor/scroll_valuator_map.hpp>
#include <sge/x11input/device/enter_event_fwd.hpp>
#include <sge/x11input/device/event_fwd.hpp>
#include <sge/x11input/device/leave_event_fwd.hpp>
#include <sge/x11input/device/object.hpp>
#include <sge/x11input/device/parameters_fwd.hpp>
#include <sge/x11input/device/window_event_fwd.hpp>
#include <awl/backends/x11/cursor/object_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace x11input
{
namespace cursor
{

class object
:
	public sge::input::cursor::object,
	public sge::x11input::device::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::x11input::device::parameters const &,
		awl::backends::x11::cursor::object const &,
		sge::x11input::cursor::entered
	);

	~object()
	override;

	void
	on_focus_in();

	void
	on_focus_out();
private:
	fcppt::signal::auto_connection
	button_callback(
		sge::input::cursor::button_callback const &
	)
	override;

	fcppt::signal::auto_connection
	move_callback(
		sge::input::cursor::move_callback const &
	)
	override;

	fcppt::signal::auto_connection
	scroll_callback(
		sge::input::cursor::scroll_callback const &
	)
	override;

	sge::input::cursor::optional_position
	position() const
	override;

	void
	mode(
		sge::input::cursor::mode
	)
	override;

	void
	on_motion(
		sge::x11input::device::window_event const &
	);

	void
	on_enter(
		sge::x11input::device::enter_event const &
	);

	void
	on_leave(
		sge::x11input::device::leave_event const &
	);

	template<
		typename Event
	>
	void
	update_position(
		sge::x11input::device::event<
			Event
		> const &
	);

	void
	on_button_down(
		sge::x11input::device::window_event const &
	);

	void
	on_button_up(
		sge::x11input::device::window_event const &
	);

	void
	button_event(
		sge::x11input::device::window_event const &,
		sge::input::cursor::button_pressed
	);

	void
	move_event();

	void
	check_grab();

	awl::backends::x11::window::object const &window_;

	awl::backends::x11::cursor::object const &cursor_;

	fcppt::signal::auto_connection_container const connections_;

	sge::input::cursor::mode mode_;

	sge::x11input::cursor::entered entered_;

	sge::input::cursor::optional_position position_;

	sge::x11input::cursor::scroll_valuator_map scroll_valuators_;

	sge::input::cursor::button_signal button_signal_;

	sge::input::cursor::move_signal move_signal_;

	sge::input::cursor::scroll_signal scroll_signal_;

	typedef
	fcppt::unique_ptr<
		sge::x11input::cursor::grab
	>
	cursor_grab_unique_ptr;

	typedef
	fcppt::optional::object<
		cursor_grab_unique_ptr
	>
	optional_cursor_grab_unique_ptr;

	optional_cursor_grab_unique_ptr cursor_grab_;
};

}
}
}

#endif
