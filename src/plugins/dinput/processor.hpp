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


#ifndef SGE_DINPUT_PROCESSOR_HPP_INCLUDED
#define SGE_DINPUT_PROCESSOR_HPP_INCLUDED

#include "cursor_ptr.hpp"
#include "device_fwd.hpp"
#include "device_ptr.hpp"
#include "di.hpp"
#include "dinput_ptr.hpp"
#include "key_converter.hpp"
#include "keyboard_ptr.hpp"
#include "mouse_ptr.hpp"
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/object_vector.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/keyboard/device_vector.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/device_vector.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/processor.hpp>
#include <sge/window/instance_ptr.hpp>
#include <awl/backends/windows/system/event/handle_ptr.hpp>
#include <awl/backends/windows/system/event/processor_ptr.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_ptr.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <awl/backends/windows/window/instance_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <vector>

namespace sge
{
namespace dinput
{

class processor
:
	public sge::input::processor
{
	FCPPT_NONCOPYABLE(
		processor
	)
public:
	explicit processor(
		dinput::dinput_ptr,
		sge::window::instance_ptr
	);

	~processor();

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

	sge::window::instance_ptr const
	window() const;
private:
	awl::backends::windows::window::event::return_type
	on_activate(
		awl::backends::windows::window::event::object const &
	);

	void
	on_handle_ready();

	typedef std::vector<
		dinput::device_ptr
	> device_vector;

	device_vector const
	all_devices() const;

	static BOOL CALLBACK
	enum_devices_callback(
		LPCDIDEVICEINSTANCE,
		LPVOID
	);

	typedef std::vector<
		dinput::keyboard_ptr
	> keyboard_vector;

	typedef std::vector<
		dinput::mouse_ptr
	> mouse_vector;

	dinput::dinput_ptr const dinput_;

	sge::window::instance_ptr const window_;
	
	awl::backends::windows::window::instance_ptr const windows_window_;

	awl::backends::windows::window::event::processor_ptr const event_processor_;

	awl::backends::windows::system::event::processor_ptr const system_processor_;

	keyboard_vector keyboards_;

	mouse_vector mice_;

	dinput::cursor_ptr const cursor_;

	dinput::key_converter key_conv_;

	awl::backends::windows::system::event::handle_ptr const event_handle_;

	bool acquired_;

	fcppt::signal::connection_manager const connections_;
};

}
}

#endif
