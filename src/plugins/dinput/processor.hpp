/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "device_fwd.hpp"
#include "di.hpp"
#include "key_converter.hpp"
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
#include <awl/backends/windows/window/instance_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>

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
	void
	dispatch();

	static BOOL CALLBACK
	di_enum_devices_callback(
		LPCDIDEVICEINSTANCE,
		LPVOID
	);

	typedef boost::ptr_vector<
		dinput::device
	> device_array;

	device_array devices_;
	
	dinput::dinput_ptr dinput_;

	sge::window::instance_ptr const window_;
	
	awl::backends::windows::window::instance_ptr const windows_window_;

	dinput::key_converter key_conv_;
};

}
}

#endif
