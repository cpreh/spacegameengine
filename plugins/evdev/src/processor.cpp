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


#include <sge/evdev/processor.hpp>
#include <sge/evdev/inotify/callback.hpp>
#include <sge/evdev/inotify/event.hpp>
#include <sge/evdev/inotify/event_type.hpp>
#include <sge/evdev/inotify/reader.hpp>
#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/add_parameters.hpp>
#include <sge/evdev/joypad/attrib.hpp>
#include <sge/evdev/joypad/init.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/remove.hpp>
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
#include <sge/window/system.hpp>
#include <awl/backends/posix/event_fwd.hpp>
#include <awl/backends/posix/posted.hpp>
#include <awl/backends/posix/processor.hpp>
#include <awl/backends/posix/processor_base.hpp>
#include <awl/system/event/processor.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/dynamic_cross_exn.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::evdev::processor::processor(
	fcppt::log::object &_log,
	sge::window::system const &_window_system
)
:
	sge::input::processor(),
	log_{
		_log
	},
	joypad_discover_(),
	joypad_remove_(),
	joypads_(),
	path_(
		"/dev/input"
	),
	processor_(
		fcppt::cast::dynamic_cross_exn<
			awl::backends::posix::processor_base &
		>(
			_window_system.awl_system_event_processor()
		).fd_processor()
	),
	start_event_(
		processor_.post(
			awl::backends::posix::callback{
				std::bind(
					&sge::evdev::processor::dev_init,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	dev_reader_()
{
}

sge::evdev::processor::~processor()
{
}

fcppt::signal::optional_auto_connection
sge::evdev::processor::keyboard_discover_callback(
	sge::input::keyboard::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::evdev::processor::keyboard_remove_callback(
	sge::input::keyboard::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::evdev::processor::mouse_discover_callback(
	sge::input::mouse::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::evdev::processor::mouse_remove_callback(
	sge::input::mouse::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::evdev::processor::focus_discover_callback(
	sge::input::focus::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::evdev::processor::focus_remove_callback(
	sge::input::focus::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::evdev::processor::cursor_discover_callback(
	sge::input::cursor::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::evdev::processor::cursor_remove_callback(
	sge::input::cursor::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::evdev::processor::joypad_discover_callback(
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
sge::evdev::processor::joypad_remove_callback(
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
sge::evdev::processor::dev_init(
	awl::backends::posix::event const &
)
{
	dev_reader_ =
		optional_inotify_reader_unique_ptr(
			fcppt::make_unique_ptr<
				sge::evdev::inotify::reader
			>(
				path_,
				processor_,
				sge::evdev::inotify::callback(
					std::bind(
						&sge::evdev::processor::dev_event,
						this,
						std::placeholders::_1
					)
				)
			)
		);

	sge::evdev::joypad::init(
		log_,
		sge::evdev::joypad::add_parameters(
			processor_,
			joypads_,
			joypad_discover_
		),
		path_
	);
}

void
sge::evdev::processor::dev_event(
	sge::evdev::inotify::event const &_event
)
{
	boost::filesystem::path const file_path(
		path_
		/
		_event.filename()
	);

	switch(
		_event.event_type()
	)
	{
	case sge::evdev::inotify::event_type::add:
		sge::evdev::joypad::add(
			log_,
			sge::evdev::joypad::add_parameters(
				processor_,
				joypads_,
				joypad_discover_
			),
			file_path
		);
		return;
	case sge::evdev::inotify::event_type::remove:
		sge::evdev::joypad::remove(
			joypads_,
			joypad_remove_,
			file_path
		);
		return;
	case sge::evdev::inotify::event_type::attrib:
		sge::evdev::joypad::attrib(
			log_,
			sge::evdev::joypad::add_parameters(
				processor_,
				joypads_,
				joypad_discover_
			),
			file_path
		);
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
