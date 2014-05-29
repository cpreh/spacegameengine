/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_event_fwd.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_event_fwd.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_event_fwd.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_event_fwd.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event_fwd.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event_fwd.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event_fwd.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event_fwd.hpp>
#include <sge/src/input/multi_processor.hpp>
#include <sge/src/input/system_ptr_vector.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::input::multi_processor::multi_processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system,
	sge::input::system_ptr_vector const &_systems
)
:
	sge::input::processor(),
	processors_(),
	keyboard_discover_(),
	keyboard_remove_(),
	mouse_discover_(),
	mouse_remove_(),
	cursor_discover_(),
	cursor_remove_(),
	joypad_discover_(),
	joypad_remove_(),
	connections_()
{
	// TODO: Initialize directly
	for(
		auto &system
		:
		_systems
	)
	{
		sge::input::processor_unique_ptr new_processor(
			system->create_processor(
				_window,
				_window_system
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			connections_,
			new_processor->keyboard_discover_callback(
				std::bind(
					&sge::input::multi_processor::on_keyboard_discover,
					this,
					std::placeholders::_1
				)
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			connections_,
			new_processor->keyboard_remove_callback(
				std::bind(
					&sge::input::multi_processor::on_keyboard_remove,
					this,
					std::placeholders::_1
				)
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			connections_,
			new_processor->mouse_discover_callback(
				std::bind(
					&sge::input::multi_processor::on_mouse_discover,
					this,
					std::placeholders::_1
				)
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			connections_,
			new_processor->mouse_remove_callback(
				std::bind(
					&sge::input::multi_processor::on_mouse_remove,
					this,
					std::placeholders::_1
				)
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			connections_,
			new_processor->cursor_discover_callback(
				std::bind(
					&sge::input::multi_processor::on_cursor_discover,
					this,
					std::placeholders::_1
				)
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			connections_,
			new_processor->cursor_remove_callback(
				std::bind(
					&sge::input::multi_processor::on_cursor_remove,
					this,
					std::placeholders::_1
				)
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			connections_,
			new_processor->joypad_discover_callback(
				std::bind(
					&sge::input::multi_processor::on_joypad_discover,
					this,
					std::placeholders::_1
				)
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			connections_,
			new_processor->joypad_remove_callback(
				std::bind(
					&sge::input::multi_processor::on_joypad_remove,
					this,
					std::placeholders::_1
				)
			)
		);

		fcppt::container::ptr::push_back_unique_ptr(
			processors_,
			std::move(
				new_processor
			)
		);
	}
}

sge::input::multi_processor::~multi_processor()
{
}

fcppt::signal::auto_connection
sge::input::multi_processor::keyboard_discover_callback(
	sge::input::keyboard::discover_callback const &_callback
)
{
	return
		keyboard_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::multi_processor::keyboard_remove_callback(
	sge::input::keyboard::remove_callback const &_callback
)
{
	return
		keyboard_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::multi_processor::mouse_discover_callback(
	sge::input::mouse::discover_callback const &_callback
)
{
	return
		mouse_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::multi_processor::mouse_remove_callback(
	sge::input::mouse::remove_callback const &_callback
)
{
	return
		mouse_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::multi_processor::cursor_discover_callback(
	sge::input::cursor::discover_callback const &_callback
)
{
	return
		cursor_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::multi_processor::cursor_remove_callback(
	sge::input::cursor::remove_callback const &_callback
)
{
	return
		cursor_remove_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::multi_processor::joypad_discover_callback(
	sge::input::joypad::discover_callback const &_callback
)
{
	return
		joypad_discover_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::multi_processor::joypad_remove_callback(
	sge::input::joypad::remove_callback const &_callback
)
{
	return
		joypad_remove_.connect(
			_callback
		);
}

void
sge::input::multi_processor::on_keyboard_discover(
	sge::input::keyboard::discover_event const &_event
)
{
	keyboard_discover_(
		_event
	);
}

void
sge::input::multi_processor::on_keyboard_remove(
	sge::input::keyboard::remove_event const &_event
)
{
	keyboard_remove_(
		_event
	);
}

void
sge::input::multi_processor::on_mouse_discover(
	sge::input::mouse::discover_event const &_event
)
{
	mouse_discover_(
		_event
	);
}

void
sge::input::multi_processor::on_mouse_remove(
	sge::input::mouse::remove_event const &_event
)
{
	mouse_remove_(
		_event
	);
}

void
sge::input::multi_processor::on_cursor_discover(
	sge::input::cursor::discover_event const &_event
)
{
	cursor_discover_(
		_event
	);
}

void
sge::input::multi_processor::on_cursor_remove(
	sge::input::cursor::remove_event const &_event
)
{
	cursor_remove_(
		_event
	);
}

void
sge::input::multi_processor::on_joypad_discover(
	sge::input::joypad::discover_event const &_event
)
{
	joypad_discover_(
		_event
	);
}

void
sge::input::multi_processor::on_joypad_remove(
	sge::input::joypad::remove_event const &_event
)
{
	joypad_remove_(
		_event
	);
}
