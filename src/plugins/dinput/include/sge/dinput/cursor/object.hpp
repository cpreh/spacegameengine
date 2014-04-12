/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_DINPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_DINPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/dinput/cursor/exclusive_mode_fwd.hpp>
#include <sge/dinput/cursor/object_fwd.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_code_fwd.hpp>
#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_code_fwd.hpp>
#include <sge/input/cursor/scroll_signal.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace dinput
{
namespace cursor
{

class object
:
	public sge::input::cursor::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		awl::backends::windows::window::event::processor &,
		awl::backends::windows::window::object &
	);

	~object();

	fcppt::signal::auto_connection
	button_callback(
		sge::input::cursor::button_callback const &
	);

	fcppt::signal::auto_connection
	move_callback(
		sge::input::cursor::move_callback const &
	);

	fcppt::signal::auto_connection
	scroll_callback(
		sge::input::cursor::scroll_callback const &
	);

	sge::input::cursor::optional_position const
	position() const;

	void
	mode(
		sge::input::cursor::mode
	);

	void
	acquire();

	void
	unacquire();

	bool
	acquired() const;
private:
	void
	make_grab();

	awl::backends::windows::window::event::return_type
	on_move(
		awl::backends::windows::window::event::object const &
	);

	awl::backends::windows::window::event::return_type
	on_button(
		awl::backends::windows::window::event::object const &,
		sge::input::cursor::button_code,
		bool down
	);

	awl::backends::windows::window::event::return_type
	on_scroll(
		awl::backends::windows::window::event::object const &,
		sge::input::cursor::scroll_code
	);

	fcppt::signal::connection_manager::container
	make_connections();

	void
	make_button_connections(
		fcppt::signal::connection_manager::container &,
		awl::backends::windows::event::type::value_type up_event,
		awl::backends::windows::event::type::value_type down_event,
		sge::input::cursor::button_code
	);

	void
	make_scroll_connection(
		fcppt::signal::connection_manager::container &,
		awl::backends::windows::event::type::value_type,
		sge::input::cursor::scroll_code
	);

	awl::backends::windows::window::event::processor &event_processor_;

	awl::backends::windows::window::object &window_;

	sge::input::cursor::button_signal button_signal_;

	sge::input::cursor::move_signal move_signal_;

	sge::input::cursor::scroll_signal scroll_signal_;

	typedef std::unique_ptr<
		sge::dinput::cursor::exclusive_mode
	> exclusive_mode_unique_ptr;

	sge::input::cursor::mode mode_;

	bool has_focus_;

	exclusive_mode_unique_ptr exclusive_mode_;

	fcppt::signal::connection_manager const connections_;
};

}
}
}

#endif
