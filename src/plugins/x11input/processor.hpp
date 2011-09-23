/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "input_context_fwd.hpp"
#include "input_method_fwd.hpp"
#include "pixmap.hpp"
#include "xi_2_1.hpp"
#include "cursor/object_ptr.hpp"
#include "cursor/pixmap.hpp"
#include "device/id.hpp"
#include "device/hierarchy_demuxer.hpp"
#include "device/hierarchy_event_fwd.hpp"
#include "device/manager.hpp"
#include "device/parameters_fwd.hpp"
#include "device/raw_demuxer.hpp"
#include "device/window_demuxer.hpp"
#include "keyboard/device_ptr.hpp"
#include "mouse/device_ptr.hpp"
#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_signal.hpp>
#include <sge/input/cursor/object_vector.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_signal.hpp>
#include <sge/input/keyboard/device_vector.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_signal.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_signal.hpp>
#include <sge/input/mouse/device_vector.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_signal.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_signal.hpp>
#include <sge/window/instance_ptr.hpp>
#include <awl/backends/x11/system/event/object_fwd.hpp>
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/system/event/processor_fwd.hpp>
#include <awl/backends/x11/window/event/object_fwd.hpp>
#include <awl/backends/x11/window/event/processor_fwd.hpp>
#include <awl/backends/x11/window/instance_shared_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
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
		sge::window::instance_ptr,
		awl::backends::x11::system::event::opcode,
		x11input::xi_2_1
	);

	~processor();
private:
	fcppt::signal::auto_connection
	keyboard_discover_callback(
		input::keyboard::discover_callback const &
	);

	fcppt::signal::auto_connection
	keyboard_remove_callback(
		input::keyboard::remove_callback const &
	);

	input::keyboard::device_vector const
	keyboards() const;

	fcppt::signal::auto_connection
	mouse_discover_callback(
		input::mouse::discover_callback const &
	);

	fcppt::signal::auto_connection
	mouse_remove_callback(
		input::mouse::remove_callback const &
	);

	input::mouse::device_vector const
	mice() const;

	fcppt::signal::auto_connection
	cursor_discover_callback(
		input::cursor::discover_callback const &
	);

	fcppt::signal::auto_connection
	cursor_remove_callback(
		input::cursor::remove_callback const &
	);

	input::cursor::object_vector const
	cursors() const;

	window::instance_ptr const
	window() const;

	x11input::device::parameters const
	device_parameters(
		x11input::device::id
	);

	x11input::keyboard::device_ptr const
	create_keyboard(
		x11input::device::id const
	);

	x11input::mouse::device_ptr const
	create_mouse(
		x11input::device::id const
	);

	x11input::cursor::object_ptr const
	create_cursor(
		x11input::device::id const
	);

	void
	on_hierarchy_changed(
		sge::x11input::device::hierarchy_event const &
	);

	template<
		typename Function
	>
	void
	for_each_device(
		Function const &
	);

	void
	on_enter(
		awl::backends::x11::window::event::object const &
	);

	void
	on_leave(
		awl::backends::x11::window::event::object const &
	);

	sge::window::instance_ptr const window_;

	awl::backends::x11::system::event::opcode const opcode_;

	awl::backends::x11::window::instance_shared_ptr const x11_window_;

	awl::backends::x11::window::event::processor &window_event_processor_;

	awl::backends::x11::system::event::processor &system_event_processor_;

	x11input::device::window_demuxer window_demuxer_;

	x11input::device::raw_demuxer raw_demuxer_;

	x11input::device::hierarchy_demuxer hierarchy_demuxer_;

	x11input::pixmap const invisible_pixmap_;

	x11input::cursor::pixmap const invisible_cursor_;

	typedef fcppt::scoped_ptr<
		x11input::input_method
	> input_method_ptr;

	input_method_ptr input_method_;

	typedef fcppt::scoped_ptr<
		x11input::input_context
	> input_context_ptr;

	input_context_ptr input_context_;

	typedef std::vector<
		x11input::keyboard::device_ptr
	> keyboard_vector;

	typedef std::vector<
		x11input::mouse::device_ptr
	> mouse_vector;

	typedef std::vector<
		x11input::cursor::object_ptr
	> cursor_vector;

	keyboard_vector keyboards_;

	mouse_vector mice_;

	cursor_vector cursors_;

	sge::input::keyboard::discover_signal keyboard_discover_;

	sge::input::keyboard::remove_signal keyboard_remove_;

	sge::input::mouse::discover_signal mouse_discover_;

	sge::input::mouse::remove_signal mouse_remove_;

	sge::input::cursor::discover_signal cursor_discover_;

	sge::input::cursor::remove_signal cursor_remove_;

	x11input::device::manager device_manager_;

	fcppt::signal::connection_manager const connections_;
};

}
}

#endif

