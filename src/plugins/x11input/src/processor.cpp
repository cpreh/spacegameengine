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
#include <X11/Xlib.h>
#include "../processor.hpp"
#include "../mouse.hpp"
#include "../keyboard.hpp"
#include "../device.hpp"
#include "../make_devices.hpp"
#include <sge/log/global.hpp>
#include <sge/window/instance.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/window/event/processor.hpp>
#include <awl/backends/x11/window/event/signal/connection.hpp>
#include <awl/backends/x11/window/event/signal/shared_connection.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/polymorphic_pointer_cast.hpp>
#include <fcppt/text.hpp>
#include <ostream>

#include <X11/extensions/XInput2.h>

#include <sge/input/exception.hpp>
#include <iostream>

sge::x11input::processor::processor(
	sge::window::instance_ptr const _window,
	int const _opcode
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
	event_processor_(
		fcppt::polymorphic_pointer_cast<
			awl::backends::x11::window::event::processor
		>(
			_window->awl_window_event_processor()	
		)
	),
	system_event_processor_(
		fcppt::polymorphic_pointer_cast<
			awl::backends::x11::system::event::processor
		>(
			_window->awl_system_event_processor()
		)
	),
	acquired_(false),
	connections_(
		fcppt::assign::make_container<
			awl::backends::x11::window::event::signal::connection_manager::container
		>(
			awl::backends::x11::window::event::signal::shared_connection(
				event_processor_->register_callback(
					FocusIn,
					std::tr1::bind(
						&processor::on_acquire,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			awl::backends::x11::window::event::signal::shared_connection(
				event_processor_->register_callback(
					FocusOut,
					std::tr1::bind(
						&processor::on_release,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			awl::backends::x11::window::event::signal::shared_connection(
				event_processor_->register_callback(
					MapNotify,
					std::tr1::bind(
						&processor::on_acquire,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			awl::backends::x11::window::event::signal::shared_connection(
				event_processor_->register_callback(
					UnmapNotify,
					std::tr1::bind(
						&processor::on_release,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	keyboards_(
		x11input::make_devices<
			x11input::keyboard
		>(
			XIMasterKeyboard,
			x11_window_,
			system_event_processor_
		)
	),
	mice_(
		x11input::make_devices<
			x11input::mouse
		>(
			XISlavePointer,
			x11_window_,
			system_event_processor_
		)
	),
	cursors_(
		x11input::make_devices<
			x11input::cursor
		>(
			XIMasterPointer,
			x11_window_,
			system_event_processor_
		)
	)
{
#if 0
	x11input::select_events(
		x11_window_,
		XIAllDevices,
		fcppt::assign::make_container<
			x11input::event_id_container
		>(
			XI_ButtonPress
		)
		(
			XI_ButtonRelease
		)
		(
			XI_Motion
		)
		(
			XI_KeyPress
		)
		(
			XI_KeyRelease
		)
	);
#endif
#if 0
	x11input::device_info const devices(
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

		switch(
			device.use
		)
		{
		case XIMasterPointer:
			cursors_.push_back(
				fcppt::make_shared_ptr<
					x11input::cursor
				>()
			);

			std::cout << "master pointer\n"; break;
			case XIMasterKeyboard: std::cout << "master keyboard\n"; break;
			case XISlavePointer: std::cout << "slave pointer\n"; break;
			case XISlaveKeyboard: std::cout << "slave keyboard\n"; break;
			case XIFloatingSlave: std::cout << "floating slave\n"; break;
		}
	}
#endif
	/*
	connections.connect(
		wnd->register_callback(
			EnterNotify,
			std::tr1::bind(
				&processor::on_acquire,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	connections.connect(
		wnd->register_callback(
			LeaveNotify,
			std::tr1::bind(
				&processor::on_release,
				this,
				std::tr1::placeholders::_1
			)
		)
	);
*/
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
}

fcppt::signal::auto_connection
sge::x11input::processor::cursor_remove_callback(
	input::cursor::remove_callback const &_callback
)
{
}

sge::input::cursor::object_vector const
sge::x11input::processor::cursors() const
{
}

sge::input::cursor::object_ptr const
sge::x11input::processor::main_cursor() const
{
}

sge::window::instance_ptr const
sge::x11input::processor::window() const
{
	return window_;
}

void
sge::x11input::processor::on_acquire(
	awl::backends::x11::window::event::object const &
)
{
	if(
		acquired_
	)
		return;

	acquired_ = true;

	FCPPT_LOG_DEBUG(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("x11: acquire window")
	);

	// TODO: what do we want to grab?
	BOOST_FOREACH(
		keyboard_vector::value_type keyboard,
		keyboards_
	)
		keyboard->grab();

	BOOST_FOREACH(
		mouse_vector::value_type mouse,
		mice_
	)
		mouse->grab();

	x11_window_->display()->sync();
}

void
sge::x11input::processor::on_release(
	awl::backends::x11::window::event::object const &
)
{
	if(
		!acquired_
	)
		return;

	acquired_ = false;

	FCPPT_LOG_DEBUG(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("x11: release window")
	);

	BOOST_FOREACH(
		keyboard_vector::reference keyboard,
		keyboards_	
	)
		keyboard->ungrab();

	BOOST_FOREACH(
		mouse_vector::reference mouse,
		mice_
	)
		mouse->ungrab();
}
