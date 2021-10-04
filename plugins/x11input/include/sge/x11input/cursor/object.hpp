//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/x11input/cursor/object_fwd.hpp>
#include <sge/x11input/cursor/optional_grab_unique_ptr.hpp>
#include <sge/x11input/cursor/scroll_valuator_map.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/window_demuxer_ref.hpp>
#include <awl/backends/x11/cursor/object_ref.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge::x11input::cursor
{

class object // NOLINT(fuchsia-multiple-inheritance)
:
	public
		sge::input::cursor::object,
	public
		fcppt::enable_shared_from_this<
			object
		>
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		sge::window::object_ref,
		fcppt::log::object_reference,
		awl::backends::x11::window::const_base_ref,
		XIDeviceInfo const &,
		sge::x11input::event::window_demuxer_ref,
		awl::backends::x11::cursor::object_ref
	);

	~object()
	override;
private:
	[[nodiscard]]
	sge::window::object &
	window() const
	override;

	[[nodiscard]]
	sge::input::cursor::optional_position
	position() const
	override;

	void
	mode(
		sge::input::cursor::mode
	)
	override;

	[[nodiscard]]
	awl::event::container
	on_event(
		XIDeviceEvent const &
	);

	[[nodiscard]]
	awl::event::container
	on_paired_event(
		XIDeviceEvent const &
	);

	[[nodiscard]]
	awl::event::container
	on_motion(
		XIDeviceEvent const &
	);

	[[nodiscard]]
	awl::event::base_unique_ptr
	on_enter(
		XIDeviceEvent const &
	);

	[[nodiscard]]
	awl::event::base_unique_ptr
	on_leave(
		XIDeviceEvent const &
	);

	void
	on_focus_out();

	[[nodiscard]]
	awl::event::base_unique_ptr
	update_position(
		XIDeviceEvent const &
	);

	[[nodiscard]]
	awl::event::base_unique_ptr
	make_position_event();

	[[nodiscard]]
	awl::event::optional_base_unique_ptr
	on_button_down(
		XIDeviceEvent const &
	);

	[[nodiscard]]
	awl::event::optional_base_unique_ptr
	on_button_up(
		XIDeviceEvent const &
	);

	[[nodiscard]]
	awl::event::optional_base_unique_ptr
	button_event(
		XIDeviceEvent const &,
		sge::input::cursor::button_pressed
	);

	void
	grab();

	void
	ungrab();

	sge::window::object_ref const sge_window_;

	sge::x11input::device::id const id_;

	fcppt::log::object_reference const log_;

	awl::backends::x11::window::const_base_ref const window_;

	awl::backends::x11::cursor::object_ref const cursor_;

	// TODO(philipp): Get rid of this
	sge::input::cursor::optional_position position_;

	bool first_enter_;

	fcppt::signal::auto_connection const event_connection_;

	fcppt::signal::auto_connection const paired_event_connection_;

	sge::input::cursor::mode mode_;

	sge::x11input::cursor::scroll_valuator_map scroll_valuators_;

	sge::x11input::cursor::optional_grab_unique_ptr cursor_grab_;
};

}

#endif
