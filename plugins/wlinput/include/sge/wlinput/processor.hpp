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
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/wlinput/map.hpp>
#include <sge/wlinput/xkb_context.hpp>
#include <sge/wlinput/cursor/object_fwd.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <awl/backends/posix/fd.hpp>
#include <awl/backends/wayland/display_fwd.hpp>
#include <awl/backends/wayland/system/event/processor_fwd.hpp>
#include <awl/backends/wayland/system/event/seat_caps_fwd.hpp>
#include <awl/backends/wayland/system/event/seat_removed_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/base_fwd.hpp>
#include <awl/event/connection_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>


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
		fcppt::log::object &,
		sge::window::object &
	);

	~processor()
	override;
private:
	sge::window::object &
	window() const
	override;

	sge::input::cursor::container
	cursors() const
	override;

	sge::input::focus::container
	foci() const
	override;

	sge::input::joypad::container
	joypads() const
	override;

	sge::input::keyboard::container
	keyboards() const
	override;

	sge::input::mouse::container
	mice() const
	override;

	awl::event::container
	on_event(
		awl::event::base const &
	);

	awl::event::container
	display_event();

	awl::event::container
	seat_caps(
		awl::backends::wayland::system::event::seat_caps const &
	);

	awl::event::container
	remove_seat(
		awl::backends::wayland::system::event::seat_removed const &
	);

	fcppt::log::object &log_;

	awl::backends::wayland::system::event::processor &system_processor_;

	sge::window::object &sge_window_;

	awl::backends::wayland::window::object &window_;

	awl::backends::wayland::display &display_;

	awl::backends::posix::fd const fd_;

	sge::wlinput::xkb_context const xkb_context_;

	awl::event::container last_events_;

	typedef
	sge::wlinput::map<
		sge::wlinput::cursor::object
	>
	cursor_map;

	typedef
	sge::wlinput::map<
		sge::wlinput::focus::object
	>
	focus_map;

	cursor_map cursors_;

	focus_map foci_;

	awl::event::connection_unique_ptr const fd_connection_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}

#endif
