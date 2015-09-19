/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_event_fwd.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_event_fwd.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/discover_event_fwd.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/focus/remove_event_fwd.hpp>
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
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::input::multi_processor::multi_processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system,
	sge::input::system_ptr_vector const &_systems
)
:
	sge::input::processor(),
	processors_(
		fcppt::algorithm::map<
			sge::input::multi_processor::processor_vector
		>(
			_systems,
			[
				&_window,
				&_window_system
			](
				sge::input::system_unique_ptr const &_system
			)
			{
				return
					_system->create_processor(
						_window,
						_window_system
					);
			}
		)
	),
	keyboard_discover_(),
	keyboard_remove_(),
	mouse_discover_(),
	mouse_remove_(),
	focus_discover_(),
	focus_remove_(),
	cursor_discover_(),
	cursor_remove_(),
	joypad_discover_(),
	joypad_remove_(),
	connections_(
		fcppt::algorithm::map_concat<
			sge::input::multi_processor::connection_container
		>(
			processors_,
			[
				this
			](
				sge::input::processor_unique_ptr const &_processor
			)
			{
				return
					fcppt::assign::make_container<
						sge::input::multi_processor::connection_container
					>(
						_processor->keyboard_discover_callback(
							sge::input::keyboard::discover_callback{
								std::bind(
									&sge::input::multi_processor::on_keyboard_discover,
									this,
									std::placeholders::_1
								)
							}
						)
					)(
						_processor->keyboard_remove_callback(
							sge::input::keyboard::remove_callback{
								std::bind(
									&sge::input::multi_processor::on_keyboard_remove,
									this,
									std::placeholders::_1
								)
							}
						)
					)(
						_processor->mouse_discover_callback(
							sge::input::mouse::discover_callback{
								std::bind(
									&sge::input::multi_processor::on_mouse_discover,
									this,
									std::placeholders::_1
								)
							}
						)
					)(
						_processor->mouse_remove_callback(
							sge::input::mouse::remove_callback{
								std::bind(
									&sge::input::multi_processor::on_mouse_remove,
									this,
									std::placeholders::_1
								)
							}
						)
					)(
						_processor->focus_discover_callback(
							sge::input::focus::discover_callback{
								std::bind(
									&sge::input::multi_processor::on_focus_discover,
									this,
									std::placeholders::_1
								)
							}
						)
					)(
						_processor->focus_remove_callback(
							sge::input::focus::remove_callback{
								std::bind(
									&sge::input::multi_processor::on_focus_remove,
									this,
									std::placeholders::_1
								)
							}
						)
					)(
						_processor->cursor_discover_callback(
							sge::input::cursor::discover_callback{
								std::bind(
									&sge::input::multi_processor::on_cursor_discover,
									this,
									std::placeholders::_1
								)
							}
						)
					)(
						_processor->cursor_remove_callback(
							sge::input::cursor::remove_callback{
								std::bind(
									&sge::input::multi_processor::on_cursor_remove,
									this,
									std::placeholders::_1
								)
							}
						)
					)(
						_processor->joypad_discover_callback(
							sge::input::joypad::discover_callback{
								std::bind(
									&sge::input::multi_processor::on_joypad_discover,
									this,
									std::placeholders::_1
								)
							}
						)
					)(
						_processor->joypad_remove_callback(
							sge::input::joypad::remove_callback{
								std::bind(
									&sge::input::multi_processor::on_joypad_remove,
									this,
									std::placeholders::_1
								)
							}
						)
					)
					.move_container();
			}
		)
	)
{
}

sge::input::multi_processor::~multi_processor()
{
}

fcppt::signal::optional_auto_connection
sge::input::multi_processor::keyboard_discover_callback(
	sge::input::keyboard::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			keyboard_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::input::multi_processor::keyboard_remove_callback(
	sge::input::keyboard::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			keyboard_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::input::multi_processor::mouse_discover_callback(
	sge::input::mouse::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			mouse_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::input::multi_processor::mouse_remove_callback(
	sge::input::mouse::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			mouse_remove_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::input::multi_processor::focus_discover_callback(
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
sge::input::multi_processor::focus_remove_callback(
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
sge::input::multi_processor::cursor_discover_callback(
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
sge::input::multi_processor::cursor_remove_callback(
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
sge::input::multi_processor::joypad_discover_callback(
	sge::input::joypad::discover_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			joypad_discover_.connect(
				_callback
			)
		};
}

fcppt::signal::optional_auto_connection
sge::input::multi_processor::joypad_remove_callback(
	sge::input::joypad::remove_callback const &_callback
)
{
	return
		fcppt::signal::optional_auto_connection{
			joypad_remove_.connect(
				_callback
			)
		};
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
sge::input::multi_processor::on_focus_discover(
	sge::input::focus::discover_event const &_event
)
{
	focus_discover_(
		_event
	);
}

void
sge::input::multi_processor::on_focus_remove(
	sge::input::focus::remove_event const &_event
)
{
	focus_remove_(
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
