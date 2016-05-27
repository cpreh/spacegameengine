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
#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/discover_event.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/wlinput/change_caps.hpp>
#include <sge/wlinput/initial_objects.hpp>
#include <sge/wlinput/processor.hpp>
#include <sge/wlinput/remove_seat.hpp>
#include <sge/wlinput/cursor/create.hpp>
#include <sge/wlinput/cursor/object.hpp>
#include <sge/wlinput/focus/create.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <awl/backends/posix/event_fwd.hpp>
#include <awl/backends/posix/posted.hpp>
#include <awl/backends/posix/processor.hpp>
#include <awl/backends/wayland/system/event/processor.hpp>
#include <awl/backends/wayland/system/event/seat_added.hpp>
#include <awl/backends/wayland/system/event/seat_added_callback.hpp>
#include <awl/backends/wayland/system/event/seat_removed.hpp>
#include <awl/backends/wayland/system/event/seat_removed_callback.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/caps_callback.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <awl/system/event/processor.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::wlinput::processor::processor(
	sge::window::object const &_window,
	sge::window::system const &_system
)
:
	sge::input::processor(),
	system_processor_{
		fcppt::cast::dynamic_exn<
			awl::backends::wayland::system::event::processor &
		>(
			_system.awl_system_event_processor()
		)
	},
	window_{
		fcppt::cast::dynamic_exn<
			awl::backends::wayland::window::object &
		>(
			_window.awl_object()
		)
	},
	xkb_context_{},
	focus_discover_{},
	focus_remove_{},
	cursor_discover_{},
	cursor_remove_{},
	cursors_(
		sge::wlinput::initial_objects<
			sge::wlinput::cursor::object,
			awl::backends::wayland::system::seat::caps::pointer
		>(
			sge::wlinput::cursor::create(
				window_
			),
			system_processor_.seats()
		)
	),
	foci_(
		sge::wlinput::initial_objects<
			sge::wlinput::focus::object,
			awl::backends::wayland::system::seat::caps::keyboard
		>(
			sge::wlinput::focus::create(
				xkb_context_,
				window_
			),
			system_processor_.seats()
		)
	),
	start_event_{
		system_processor_.fd_processor().post(
			awl::backends::posix::callback{
				std::bind(
					&sge::wlinput::processor::init,
					this,
					std::placeholders::_1
				)
			}
		)
	},
	seat_added_connection_{
		system_processor_.seat_added_callback(
			awl::backends::wayland::system::event::seat_added_callback{
				std::bind(
					&sge::wlinput::processor::add_seat,
					this,
					std::placeholders::_1
				)
			}
		)
	},
	seat_removed_connection_{
		system_processor_.seat_removed_callback(
			awl::backends::wayland::system::event::seat_removed_callback{
				std::bind(
					&sge::wlinput::processor::remove_seat,
					this,
					std::placeholders::_1
				)
			}
		)
	},
	seat_connections_{}
{
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

void
sge::wlinput::processor::init(
	awl::backends::posix::event const &
)
{
	for(
		auto const &focus
		:
		foci_
	)
		focus_discover_(
			sge::input::focus::discover_event{
				*focus.second
			}
		);

	for(
		auto const &cursor
		:
		cursors_
	)
		cursor_discover_(
			sge::input::cursor::discover_event{
				*cursor.second
			}
		);
}

void
sge::wlinput::processor::add_seat(
	awl::backends::wayland::system::event::seat_added const &_seat
)
{
	FCPPT_ASSERT_ERROR(
		seat_connections_.insert(
			std::make_pair(
				_seat.get().name(),
				_seat.get().caps_callback(
					awl::backends::wayland::system::seat::caps_callback{
						std::bind(
							&sge::wlinput::processor::seat_caps,
							this,
							fcppt::make_cref(
								_seat.get()
							),
							std::placeholders::_1
						)
					}
				)
			)
		).second
	);
}

void
sge::wlinput::processor::seat_caps(
	fcppt::reference<
		awl::backends::wayland::system::seat::object const
	> const _seat,
	awl::backends::wayland::system::seat::caps_field
)
{
	sge::wlinput::change_caps<
		awl::backends::wayland::system::seat::caps::keyboard
	>(
		sge::wlinput::focus::create(
			xkb_context_,
			window_
		),
		foci_,
		focus_discover_,
		focus_remove_,
		_seat.get()
	);

	sge::wlinput::change_caps<
		awl::backends::wayland::system::seat::caps::pointer
	>(
		sge::wlinput::cursor::create(
			window_
		),
		cursors_,
		cursor_discover_,
		cursor_remove_,
		_seat.get()
	);
}

void
sge::wlinput::processor::remove_seat(
	awl::backends::wayland::system::event::seat_removed const &_seat
)
{
	sge::wlinput::remove_seat<
		awl::backends::wayland::system::seat::caps::keyboard
	>(
		foci_,
		focus_remove_,
		_seat.get()
	);

	sge::wlinput::remove_seat<
		awl::backends::wayland::system::seat::caps::pointer
	>(
		cursors_,
		cursor_remove_,
		_seat.get()
	);
}
