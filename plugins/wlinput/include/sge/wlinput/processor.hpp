//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_PROCESSOR_HPP_INCLUDED
#define SGE_WLINPUT_PROCESSOR_HPP_INCLUDED

#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/wlinput/map.hpp>
#include <sge/wlinput/xkb_context.hpp>
#include <sge/wlinput/cursor/object_fwd.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <awl/backends/posix/fd.hpp>
#include <awl/backends/wayland/display_ref.hpp>
#include <awl/backends/wayland/system/event/processor_fwd.hpp>
#include <awl/backends/wayland/system/event/seat_caps_fwd.hpp>
#include <awl/backends/wayland/system/event/seat_removed_fwd.hpp>
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/base_fwd.hpp>
#include <awl/event/connection_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge::wlinput
{

class processor
:
	public sge::input::processor
{
	FCPPT_NONMOVABLE(
		processor
	);
public:
	processor(
		fcppt::log::object_reference,
		sge::window::object_ref
	);

	~processor()
	override;
private:
	[[nodiscard]]
	sge::window::object &
	window() const
	override;

	[[nodiscard]]
	sge::input::cursor::container
	cursors() const
	override;

	[[nodiscard]]
	sge::input::focus::container
	foci() const
	override;

	[[nodiscard]]
	sge::input::joypad::container
	joypads() const
	override;

	[[nodiscard]]
	sge::input::keyboard::container
	keyboards() const
	override;

	[[nodiscard]]
	sge::input::mouse::container
	mice() const
	override;

	[[nodiscard]]
	awl::event::container
	on_event(
		awl::event::base const &
	);

	[[nodiscard]]
	awl::event::container
	display_event();

	[[nodiscard]]
	awl::event::container
	seat_caps(
		awl::backends::wayland::system::event::seat_caps const &
	);

	[[nodiscard]]
	awl::event::container
	remove_seat(
		awl::backends::wayland::system::event::seat_removed const &
	);

	fcppt::log::object_reference const log_;

	fcppt::reference<
		awl::backends::wayland::system::event::processor
	> const system_processor_;

	sge::window::object_ref const sge_window_;

	awl::backends::wayland::window::object_ref const window_;

	awl::backends::wayland::display_ref const display_;

	awl::backends::posix::fd const fd_;

	sge::wlinput::xkb_context xkb_context_;

	awl::event::container last_events_;

	using
	cursor_map
	=
	sge::wlinput::map<
		sge::wlinput::cursor::object
	>;

	using
	focus_map
	=
	sge::wlinput::map<
		sge::wlinput::focus::object
	>;

	cursor_map cursors_;

	focus_map foci_;

	awl::event::connection_unique_ptr const fd_connection_;

	fcppt::signal::auto_connection const event_connection_;
};

}

#endif
