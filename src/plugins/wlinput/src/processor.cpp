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


#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system.hpp>
#include <sge/wlinput/initial_objects.hpp>
#include <sge/wlinput/processor.hpp>
#include <sge/wlinput/cursor/object.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <awl/backends/wayland/system/event/processor.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/system/event/processor.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>


sge::wlinput::processor::processor(
	sge::window::object const &,
	sge::window::system const &_system
)
:
	sge::input::processor(),
	system_processor_{
		fcppt::cast::dynamic<
			awl::backends::wayland::system::event::processor &
		>(
			_system.awl_system_event_processor()
		)
	},
	focus_discover_{},
	focus_remove_{},
	cursor_discover_{},
	cursor_remove_{},
	cursors_(
		sge::wlinput::initial_objects<
			sge::wlinput::cursor::object,
			awl::backends::wayland::system::seat::caps::pointer
		>(
			system_processor_.seats()
		)
	),
	foci_(
		sge::wlinput::initial_objects<
			sge::wlinput::focus::object,
			awl::backends::wayland::system::seat::caps::keyboard
		>(
			system_processor_.seats()
		)
	)
{
	// FIXME: Add eventfd here!
}

sge::wlinput::processor::~processor()
{
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::keyboard_discover_callback(
	sge::input::keyboard::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::keyboard_remove_callback(
	sge::input::keyboard::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::mouse_discover_callback(
	sge::input::mouse::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::mouse_remove_callback(
	sge::input::mouse::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::focus_discover_callback(
	sge::input::focus::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			focus_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::focus_remove_callback(
	sge::input::focus::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			focus_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::cursor_discover_callback(
	sge::input::cursor::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			cursor_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::cursor_remove_callback(
	sge::input::cursor::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			cursor_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::joypad_discover_callback(
	sge::input::joypad::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wlinput::processor::joypad_remove_callback(
	sge::input::joypad::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}
