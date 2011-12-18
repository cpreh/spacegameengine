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

#include <sge/dinput/di.hpp>
#include <sge/dinput/dinput_device_scoped_ptr.hpp>
#include <sge/dinput/cursor/object_ptr.hpp>
#include <sge/dinput/device/object_fwd.hpp>
#include <sge/dinput/device/object_ptr.hpp>
#include <sge/dinput/keyboard/key_converter.hpp>
#include <sge/dinput/keyboard/device_ptr.hpp>
#include <sge/dinput/mouse/device_ptr.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/object_vector.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/joypad/device_vector.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/keyboard/device_vector.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/device_vector.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/backends/windows/system/event/handle_fwd.hpp>
#include <awl/backends/windows/system/event/processor_fwd.hpp>
#include <awl/backends/windows/window/instance_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


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
	);
public:
	processor(
		sge::window::object const &,
		sge::window::system const &
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

	fcppt::signal::auto_connection
	joypad_discover_callback(
		input::joypad::discover_callback const &
	);

	fcppt::signal::auto_connection
	joypad_remove_callback(
		input::joypad::remove_callback const &
	);

	input::joypad::device_vector const
	joypads() const;
private:
	awl::backends::windows::window::event::return_type
	on_activate(
		awl::backends::windows::window::event::object const &
	);

	void
	on_handle_ready();

	typedef std::vector<
		dinput::device::object_ptr
	> device_vector;

	device_vector const
	all_devices() const;

	static BOOL CALLBACK
	enum_devices_callback(
		LPCDIDEVICEINSTANCE,
		LPVOID
	);

	typedef std::vector<
		dinput::keyboard::device_ptr
	> keyboard_vector;

	typedef std::vector<
		dinput::mouse::device_ptr
	> mouse_vector;

	typedef fcppt::scoped_ptr<
		IDirectInput8,
		fcppt::com_deleter
	> dinput_scoped_ptr;

	dinput_scoped_ptr const dinput_;

	awl::backends::windows::window::instance &windows_window_;

	awl::backends::windows::window::event::processor &event_processor_;

	awl::backends::windows::system::event::processor &system_processor_;

	keyboard_vector keyboards_;

	mouse_vector mice_;

	dinput::dinput_device_scoped_ptr const system_mouse_;

	dinput::cursor::object_ptr const cursor_;

	dinput::keyboard::key_converter key_conv_;

	typedef fcppt::scoped_ptr<
		awl::backends::windows::system::event::handle
	> event_handle_scoped_ptr;

	event_handle_scoped_ptr const event_handle_;

	bool acquired_;

	fcppt::signal::connection_manager const connections_;
};

}
}

#endif
