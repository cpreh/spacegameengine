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
#include <sge/window/system_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


sge::evdev::processor::processor(
	sge::window::object const &_window,
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
	joypad_remove_()
{
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
