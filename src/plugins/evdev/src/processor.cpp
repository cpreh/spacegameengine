/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/evdev/processor.hpp>
#include <sge/evdev/eventfd/callback.hpp>
#include <sge/evdev/eventfd/object.hpp>
#include <sge/evdev/inotify/callback.hpp>
#include <sge/evdev/inotify/event.hpp>
#include <sge/evdev/inotify/event_type.hpp>
#include <sge/evdev/inotify/reader.hpp>
#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/init.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/remove.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/tr1/functional.hpp>


sge::evdev::processor::processor(
	sge::window::object const &,
	sge::window::system const &_window_system
)
:
	sge::input::processor(),
	keyboard_discover_(),
	keyboard_remove_(),
	mouse_discover_(),
	mouse_remove_(),
	cursor_discover_(),
	cursor_remove_(),
	joypad_discover_(),
	joypad_remove_(),
	joypads_(),
	path_(
		"/dev/input"
	),
	system_processor_(
		dynamic_cast<
			awl::backends::x11::system::event::processor &
		>(
			_window_system.awl_system_event_processor()
		)
	),
	eventfd_(
		fcppt::make_unique_ptr<
			sge::evdev::eventfd::object
		>(
			fcppt::ref(
				system_processor_
			),
			sge::evdev::eventfd::callback(
				std::tr1::bind(
					&sge::evdev::processor::dev_init,
					this
				)
			)
		)
	),
	dev_reader_()
{
	eventfd_->write();
}

sge::evdev::processor::~processor()
{
}

fcppt::signal::auto_connection
sge::evdev::processor::keyboard_discover_callback(
	sge::input::keyboard::discover_callback const &_callback
)
{
	return
		keyboard_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::processor::keyboard_remove_callback(
	sge::input::keyboard::remove_callback const &_callback
)
{
	return
		keyboard_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::processor::mouse_discover_callback(
	sge::input::mouse::discover_callback const &_callback
)
{
	return
		mouse_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::processor::mouse_remove_callback(
	sge::input::mouse::remove_callback const &_callback
)
{
	return
		mouse_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::processor::cursor_discover_callback(
	sge::input::cursor::discover_callback const &_callback
)
{
	return
		cursor_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::processor::cursor_remove_callback(
	sge::input::cursor::remove_callback const &_callback
)
{
	return
		cursor_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::processor::joypad_discover_callback(
	sge::input::joypad::discover_callback const &_callback
)
{
	return
		joypad_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::processor::joypad_remove_callback(
	sge::input::joypad::remove_callback const &_callback
)
{
	return
		joypad_remove_.connect(
			_callback
		);
}

void
sge::evdev::processor::dev_init()
{
	eventfd_->read();

	dev_reader_.take(
		fcppt::make_unique_ptr<
			sge::evdev::inotify::reader
		>(
			fcppt::cref(
				path_
			),
			fcppt::ref(
				system_processor_
			),
			sge::evdev::inotify::callback(
				std::tr1::bind(
					&sge::evdev::processor::dev_event,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	);

	sge::evdev::joypad::init(
		system_processor_,
		joypads_,
		joypad_discover_,
		path_
	);
}

void
sge::evdev::processor::dev_event(
	sge::evdev::inotify::event const &_event
)
{
	switch(
		_event.event_type()
	)
	{
	case sge::evdev::inotify::event_type::add:
		sge::evdev::joypad::add(
			system_processor_,
			joypads_,
			joypad_discover_,
			path_
			/
			_event.filename()
		);
		return;
	case sge::evdev::inotify::event_type::remove:
		sge::evdev::joypad::remove(
			joypads_,
			joypad_remove_,
			path_
			/
			_event.filename()
		);
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
