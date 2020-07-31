//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_PROCESSOR_HPP_INCLUDED
#define SGE_X11INPUT_PROCESSOR_HPP_INCLUDED

#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/x11input/opcode.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/map.hpp>
#include <sge/x11input/event/handler.hpp>
#include <sge/x11input/event/raw_demuxer.hpp>
#include <sge/x11input/event/type.hpp>
#include <sge/x11input/event/window_demuxer.hpp>
#include <sge/x11input/xim/optional_method_unique_ptr.hpp>
#include <awl/backends/x11/cursor/object_unique_ptr.hpp>
#include <awl/backends/x11/system/event/generic_fwd.hpp>
#include <awl/backends/x11/window/base_unique_ptr.hpp>
#include <awl/backends/x11/window/object_ref.hpp>
#include <awl/event/base_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/strong_typedef_std_hash.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
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
		sge::window::object_ref,
		sge::x11input::opcode
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

	using
	optional_event_container
	=
	fcppt::optional::object<
		awl::event::container
	>;

	[[nodiscard]]
	awl::event::container
	system_event(
		awl::event::base const &
	);

	[[nodiscard]]
	optional_event_container
	extension_event(
		awl::backends::x11::system::event::generic const &
	);

	[[nodiscard]]
	awl::event::container
	hierarchy_event(
		XIHierarchyEvent const &
	);

	[[nodiscard]]
	awl::event::optional_base_unique_ptr
	hierarchy_info(
		XIHierarchyInfo const &
	);

	[[nodiscard]]
	awl::event::optional_base_unique_ptr
	add_device(
		XIDeviceInfo const &
	);

	[[nodiscard]]
	awl::event::optional_base_unique_ptr
	remove_device(
		XIHierarchyInfo const &
	);

	[[nodiscard]]
	sge::input::focus::shared_ptr
	add_focus(
		XIDeviceInfo const &
	);

	[[nodiscard]]
	sge::input::keyboard::shared_ptr
	add_keyboard(
		XIDeviceInfo const &
	);

	[[nodiscard]]
	sge::input::cursor::shared_ptr
	add_cursor(
		XIDeviceInfo const &
	);

	[[nodiscard]]
	sge::input::mouse::shared_ptr
	add_mouse(
		XIDeviceInfo const &
	);

	fcppt::log::object_reference const log_;

	sge::x11input::opcode const opcode_;

	sge::window::object_ref const window_;

	awl::backends::x11::window::object_ref const x11_window_;

	awl::backends::x11::window::base_unique_ptr const root_window_;

	awl::backends::x11::cursor::object_unique_ptr const invisible_cursor_;

	sge::x11input::xim::optional_method_unique_ptr const xim_method_;

	sge::x11input::event::window_demuxer window_demuxer_;

	sge::x11input::event::raw_demuxer raw_demuxer_;

	using
	focus_map
	=
	sge::x11input::device::map<
		sge::input::focus::object
	>;

	using
	keyboard_map
	=
	sge::x11input::device::map<
		sge::input::keyboard::device
	>;

	using
	cursor_map
	=
	sge::x11input::device::map<
		sge::input::cursor::object
	>;

	using
	mouse_map
	=
	sge::x11input::device::map<
		sge::input::mouse::device
	>;

	focus_map foci_;

	keyboard_map keyboards_;

	cursor_map cursors_;

	mouse_map mice_;

	using
	handler_map
	=
	std::unordered_map<
		sge::x11input::event::type,
		sge::x11input::event::handler
	>;

	handler_map const handlers_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}

#endif
