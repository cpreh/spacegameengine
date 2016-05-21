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


#ifndef SGE_WLINPUT_PROCESSOR_HPP_INCLUDED
#define SGE_WLINPUT_PROCESSOR_HPP_INCLUDED

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
#include <sge/window/system_fwd.hpp>
#include <sge/wlinput/cursor/object_fwd.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <awl/backends/posix/event_fwd.hpp>
#include <awl/backends/posix/posted_unique_ptr.hpp>
#include <awl/backends/wayland/registry_id.hpp>
#include <awl/backends/wayland/system/event/processor_fwd.hpp>
#include <awl/backends/wayland/system/event/seat_fwd.hpp>
#include <awl/backends/wayland/system/seat/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/optional_auto_connection_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wlinput
{

class processor
:
	public sge::input::processor
{
	FCPPT_NONCOPYABLE(
		processor
	);
public:
	processor(
		sge::window::object const &,
		sge::window::system const &
	);

	~processor()
	override;
private:
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
	joypad_discover_callback(
		sge::input::joypad::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	joypad_remove_callback(
		sge::input::joypad::remove_callback const &
	)
	override;

	void
	init(
		awl::backends::posix::event const &
	);

	void
	seat_changed(
		awl::backends::wayland::system::event::seat const &
	);

	void
	add_seat(
		awl::backends::wayland::system::seat::object const &
	);

	void
	remove_seat(
		awl::backends::wayland::system::seat::object const &
	);

	awl::backends::wayland::system::event::processor &system_processor_;

	sge::input::focus::discover_signal focus_discover_;

	sge::input::focus::remove_signal focus_remove_;

	sge::input::cursor::discover_signal cursor_discover_;

	sge::input::cursor::remove_signal cursor_remove_;

	typedef
	fcppt::unique_ptr<
		sge::wlinput::cursor::object
	>
	cursor_unique_ptr;

	typedef
	std::unordered_map<
		awl::backends::wayland::registry_id,
		cursor_unique_ptr
	>
	cursor_map;

	typedef
	fcppt::unique_ptr<
		sge::wlinput::focus::object
	>
	focus_unique_ptr;

	typedef
	std::unordered_map<
		awl::backends::wayland::registry_id,
		focus_unique_ptr
	>
	focus_map;

	cursor_map cursors_;

	focus_map foci_;

	awl::backends::posix::posted_unique_ptr const start_event_;

	fcppt::signal::auto_connection const seat_connection_;
};

}
}

#endif
