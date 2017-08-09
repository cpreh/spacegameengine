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
#include <awl/backends/x11/system/event/object_fwd.hpp>
#include <awl/backends/x11/system/event/processor_fwd.hpp>
#include <awl/backends/x11/window/base_unique_ptr.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <awl/event/base_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef_std_hash.hpp>
#include <fcppt/log/object_fwd.hpp>
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
	FCPPT_NONCOPYABLE(
		processor
	);
public:
	processor(
		fcppt::log::object &,
		sge::window::object &,
		sge::x11input::opcode
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

	typedef
	fcppt::optional::object<
		awl::event::container
	>
	optional_event_container;

	awl::event::container
	system_event(
		awl::event::base const &
	);

	optional_event_container
	extension_event(
		awl::backends::x11::system::event::generic const &
	);

	awl::event::container
	hierarchy_event(
		XIHierarchyEvent const &
	);

	awl::event::optional_base_unique_ptr
	hierarchy_info(
		XIHierarchyInfo const &
	);

	awl::event::optional_base_unique_ptr
	add_device(
		XIDeviceInfo const &
	);

	awl::event::optional_base_unique_ptr
	remove_device(
		XIHierarchyInfo const &
	);

	sge::input::focus::shared_ptr
	add_focus(
		XIDeviceInfo const &
	);

	sge::input::keyboard::shared_ptr
	add_keyboard(
		XIDeviceInfo const &
	);

	sge::input::cursor::shared_ptr
	add_cursor(
		XIDeviceInfo const &
	);

	sge::input::mouse::shared_ptr
	add_mouse(
		XIDeviceInfo const &
	);

	fcppt::log::object &log_;

	sge::x11input::opcode const opcode_;

	sge::window::object &window_;

	awl::backends::x11::window::object &x11_window_;

	awl::backends::x11::window::base_unique_ptr const root_window_;

	awl::backends::x11::cursor::object_unique_ptr const invisible_cursor_;

	sge::x11input::xim::optional_method_unique_ptr const xim_method_;

	sge::x11input::event::window_demuxer window_demuxer_;

	sge::x11input::event::raw_demuxer raw_demuxer_;

	typedef
	sge::x11input::device::map<
		sge::input::focus::object
	>
	focus_map;

	typedef
	sge::x11input::device::map<
		sge::input::keyboard::device
	>
	keyboard_map;

	typedef
	sge::x11input::device::map<
		sge::input::cursor::object
	>
	cursor_map;

	typedef
	sge::x11input::device::map<
		sge::input::mouse::device
	>
	mouse_map;

	focus_map foci_;

	keyboard_map keyboards_;

	cursor_map cursors_;

	mouse_map mice_;

	typedef
	std::unordered_map<
		sge::x11input::event::type,
		sge::x11input::event::handler
	>
	handler_map;

	handler_map const handlers_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}

#endif
