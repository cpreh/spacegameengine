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
#include <sge/input/keyboard/discover_signal.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_signal.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_signal.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_signal.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <sge/x11input/create_parameters_fwd.hpp>
#include <sge/x11input/cursor/object_unique_ptr.hpp>
#include <sge/x11input/device/hierarchy_demuxer.hpp>
#include <sge/x11input/device/hierarchy_event_fwd.hpp>
#include <sge/x11input/device/parameters_fwd.hpp>
#include <sge/x11input/device/raw_demuxer.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/manager/object.hpp>
#include <sge/x11input/focus/object_unique_ptr.hpp>
#include <sge/x11input/keyboard/device_unique_ptr.hpp>
#include <sge/x11input/mouse/device_unique_ptr.hpp>
#include <sge/x11input/xim/optional_method_unique_ptr.hpp>
#include <awl/backends/x11/atom.hpp>
#include <awl/backends/x11/cursor/object_unique_ptr.hpp>
#include <awl/backends/x11/system/event/object_fwd.hpp>
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/system/event/processor_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <awl/backends/x11/window/object_unique_ptr.hpp>
#include <awl/backends/x11/window/event/object_fwd.hpp>
#include <awl/backends/x11/window/event/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/optional_auto_connection_fwd.hpp>


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
		sge::window::object const &,
		sge::window::system const &,
		awl::backends::x11::system::event::opcode
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

	sge::x11input::device::parameters
	device_parameters(
		sge::x11input::create_parameters const &
	);

	sge::x11input::keyboard::device_unique_ptr
	create_keyboard(
		sge::x11input::create_parameters const &
	);

	sge::x11input::mouse::device_unique_ptr
	create_mouse(
		sge::x11input::create_parameters const &
	);

	sge::x11input::focus::object_unique_ptr
	create_focus(
		sge::x11input::create_parameters const &
	);

	sge::x11input::cursor::object_unique_ptr
	create_cursor(
		sge::x11input::create_parameters const &
	);

	void
	on_hierarchy_changed(
		sge::x11input::device::hierarchy_event const &
	);

	template<
		typename Function
	>
	void
	for_each_cursor(
		Function const &
	);

	void
	on_client_message(
		awl::backends::x11::window::event::object const &
	);

	fcppt::log::object &log_;

	awl::backends::x11::system::event::opcode const opcode_;

	awl::backends::x11::window::object const &x11_window_;

	awl::backends::x11::window::event::processor &window_event_processor_;

	awl::backends::x11::system::event::processor &system_event_processor_;

	sge::x11input::device::window_demuxer window_demuxer_;

	awl::backends::x11::window::object_unique_ptr const root_window_;

	sge::x11input::device::raw_demuxer raw_demuxer_;

	sge::x11input::device::hierarchy_demuxer hierarchy_demuxer_;

	awl::backends::x11::cursor::object_unique_ptr const invisible_cursor_;

	sge::x11input::xim::optional_method_unique_ptr const xim_method_;

	sge::input::keyboard::discover_signal keyboard_discover_;

	sge::input::keyboard::remove_signal keyboard_remove_;

	sge::input::mouse::discover_signal mouse_discover_;

	sge::input::mouse::remove_signal mouse_remove_;

	sge::input::focus::discover_signal focus_discover_;

	sge::input::focus::remove_signal focus_remove_;

	sge::input::cursor::discover_signal cursor_discover_;

	sge::input::cursor::remove_signal cursor_remove_;

	sge::x11input::device::manager::object device_manager_;

	awl::backends::x11::atom const init_atom_;

	fcppt::signal::auto_connection_container const connections_;
};

}
}

#endif
