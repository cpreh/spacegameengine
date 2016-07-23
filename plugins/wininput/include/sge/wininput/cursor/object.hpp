/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_WININPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_WININPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_code_fwd.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_code_fwd.hpp>
#include <sge/input/cursor/scroll_signal.hpp>
#include <sge/wininput/has_focus.hpp>
#include <sge/wininput/cursor/exclusive_mode_fwd.hpp>
#include <sge/wininput/cursor/object_fwd.hpp>
#include <awl/backends/windows/message_type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace wininput
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
		awl::backends::windows::window::object &,
		sge::wininput::has_focus
	);

	~object()
	override;

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
	focus_out();
private:
	void
	focus_in();

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
		sge::input::cursor::button_pressed
	);

	awl::backends::windows::window::event::return_type
	on_scroll(
		awl::backends::windows::window::event::object const &,
		sge::input::cursor::scroll_code
	);

	fcppt::signal::auto_connection_container
	make_button_connections(
		awl::backends::windows::message_type::value_type up_event,
		awl::backends::windows::message_type::value_type down_event,
		sge::input::cursor::button_code
	);

	fcppt::signal::auto_connection
	make_scroll_connection(
		awl::backends::windows::message_type::value_type,
		sge::input::cursor::scroll_code
	);

	awl::backends::windows::window::event::processor &event_processor_;

	awl::backends::windows::window::object &window_;

	sge::input::cursor::button_signal button_signal_;

	sge::input::cursor::move_signal move_signal_;

	sge::input::cursor::scroll_signal scroll_signal_;

	typedef
	fcppt::unique_ptr<
		sge::wininput::cursor::exclusive_mode
	>
	exclusive_mode_unique_ptr;

	typedef
	fcppt::optional::object<
		exclusive_mode_unique_ptr
	>
	optional_exclusive_mode_unique_ptr;

	sge::input::cursor::mode mode_;

	sge::wininput::has_focus has_focus_;

	optional_exclusive_mode_unique_ptr exclusive_mode_;

	fcppt::signal::auto_connection_container const connections_;
};

}
}
}

#endif
