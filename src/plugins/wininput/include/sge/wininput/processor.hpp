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


#ifndef SGE_WININPUT_PROCESSOR_HPP_INCLUDED
#define SGE_WININPUT_PROCESSOR_HPP_INCLUDED

#include <sge/wininput/cursor/object_fwd.hpp>
#include <sge/wininput/focus/object_fwd.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_signal.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_signal.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/discover_signal.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/focus/remove_signal.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type_fwd.hpp>
#include <awl/backends/windows/window/event/scoped_user_message.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/optional_auto_connection_fwd.hpp>


namespace sge
{
namespace wininput
{

class processor
:
	public sge::input::processor
{
	FCPPT_NONCOPYABLE(
		processor
	);
public:
	explicit
	processor(
		sge::window::object const &
	);

	~processor()
	override;

	fcppt::signal::optional_auto_connection
	keyboard_discover_callback(
		sge::input::keyboard::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	keyboard_remove_callback(
		sge::input::keyboard::remove_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	mouse_discover_callback(
		sge::input::mouse::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	mouse_remove_callback(
		sge::input::mouse::remove_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	cursor_discover_callback(
		sge::input::cursor::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	cursor_remove_callback(
		sge::input::cursor::remove_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	focus_discover_callback(
		sge::input::focus::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	focus_remove_callback(
		sge::input::focus::remove_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	joypad_discover_callback(
		sge::input::joypad::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	joypad_remove_callback(
		sge::input::joypad::remove_callback const &
	)
	override;
private:
	awl::backends::windows::window::event::return_type
	on_focus_out(
		awl::backends::windows::window::event::object const &
	);

	awl::backends::windows::window::event::return_type
	on_init(
		awl::backends::windows::window::event::object const &
	);

	awl::backends::windows::window::object &windows_window_;

	awl::backends::windows::window::event::processor &event_processor_;

	sge::input::focus::discover_signal focus_discover_;

	sge::input::focus::remove_signal focus_remove_;

	sge::input::cursor::discover_signal cursor_discover_;

	sge::input::cursor::remove_signal cursor_remove_;

	awl::backends::windows::window::event::scoped_user_message const init_message_;

	fcppt::signal::auto_connection_container const connections_;

	typedef
	fcppt::unique_ptr<
		sge::wininput::cursor::object
	>
	cursor_unique_ptr;

	typedef
	fcppt::optional::object<
		cursor_unique_ptr
	>
	optional_cursor_unique_ptr;

	optional_cursor_unique_ptr cursor_;

	typedef
	fcppt::unique_ptr<
		sge::wininput::focus::object
	>
	focus_unique_ptr;

	typedef
	fcppt::optional::object<
		focus_unique_ptr
	>
	optional_focus_unique_ptr;

	optional_focus_unique_ptr focus_;
};

}
}

#endif
