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


#include <boost/foreach.hpp> // some header breaks BOOST_FOREACH
#include "../processor.hpp"
#include "../mouse.hpp"
#include "../keyboard.hpp"
#include "../cursor.hpp"
#include "../device/info.hpp"
#include "../device/parameters.hpp"
#include <sge/window/instance.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/window/root.hpp>
#include <awl/backends/x11/window/event/processor.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/polymorphic_pointer_cast.hpp>
#include <fcppt/text.hpp>
#include <ostream>
#include <X11/extensions/XInput2.h>

sge::x11input::processor::processor(
	sge::window::instance_ptr const _window,
	awl::backends::x11::system::event::opcode const _opcode
)
:
	window_(_window),
	opcode_(_opcode),
	x11_window_(
		fcppt::polymorphic_pointer_cast<
			awl::backends::x11::window::instance
		>(
			_window->awl_instance()
		)
	),
	system_event_processor_(
		fcppt::polymorphic_pointer_cast<
			awl::backends::x11::system::event::processor
		>(
			_window->awl_system_event_processor()
		)
	),
	window_demuxer_(
		system_event_processor_,
		opcode_,
		x11_window_
	),
	raw_demuxer_(
		system_event_processor_,
		opcode_,
		awl::backends::x11::window::root(
			x11_window_->display(),
			x11_window_->screen()
		)
	),
	keyboards_(),
	mice_(),
	cursors_()
{
	x11input::device::info const devices(
		x11_window_->display(),
		XIAllDevices
	);

	for(
		int index = 0;
		index < devices.size();
		++index
	)
	{
		XIDeviceInfo const &device(
			devices[index]
		);

		x11input::device::parameters const param(
			x11input::device::id(
				device.deviceid
			),
			opcode_,
			x11_window_,
			window_demuxer_,
			raw_demuxer_
		);

		switch(
			device.use
		)
		{
		case XIMasterKeyboard:
			keyboards_.push_back(
				fcppt::make_shared_ptr<
					x11input::keyboard
				>(
					param
				)
			);
			break;
		case XISlavePointer:
			mice_.push_back(
				fcppt::make_shared_ptr<
					x11input::mouse
				>(
					param
				)
			);
			break;
		case XIMasterPointer:
			cursors_.push_back(
				fcppt::make_shared_ptr<
					x11input::cursor
				>(
					param
				)
			);
			break;
		}
	}
}

sge::x11input::processor::~processor()
{
}

fcppt::signal::auto_connection
sge::x11input::processor::keyboard_discover_callback(
	input::keyboard::discover_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

fcppt::signal::auto_connection
sge::x11input::processor::keyboard_remove_callback(
	input::keyboard::remove_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

sge::input::keyboard::device_vector const
sge::x11input::processor::keyboards() const
{
	return
		input::keyboard::device_vector(
			keyboards_.begin(),
			keyboards_.end()
		);
}

fcppt::signal::auto_connection
sge::x11input::processor::mouse_discover_callback(
	input::mouse::discover_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

fcppt::signal::auto_connection
sge::x11input::processor::mouse_remove_callback(
	input::mouse::remove_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

sge::input::mouse::device_vector const
sge::x11input::processor::mice() const
{
	return
		input::mouse::device_vector(
			mice_.begin(),
			mice_.end()
		);
}

fcppt::signal::auto_connection
sge::x11input::processor::cursor_discover_callback(
	input::cursor::discover_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

fcppt::signal::auto_connection
sge::x11input::processor::cursor_remove_callback(
	input::cursor::remove_callback const &_callback
)
{
	return fcppt::signal::auto_connection();
}

sge::input::cursor::object_vector const
sge::x11input::processor::cursors() const
{
	return
		input::cursor::object_vector(
			cursors_.begin(),
			cursors_.end()
		);
}

sge::window::instance_ptr const
sge::x11input::processor::window() const
{
	return window_;
}
