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


#include <sge/wininput/logger.hpp>
#include <sge/wininput/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_event.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <awl/backends/windows/event/lparam.hpp>
#include <awl/backends/windows/event/post_message.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/event/wparam.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/backends/windows/window/event/callback.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/window/has_focus.hpp>
#include <awl/window/event/focus_in_callback.hpp>
#include <awl/window/event/focus_in_fwd.hpp>
#include <awl/window/event/focus_out_callback.hpp>
#include <awl/window/event/focus_out_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::wininput::processor::processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system
)
:
	awl_system_(
		_window_system.awl_system()
	),
	windows_window_(
		fcppt::cast::static_downcast<
			awl::backends::windows::window::object &
		>(
			_window.awl_object()
		)
	),
	event_processor_(
		fcppt::cast::static_downcast<
			awl::backends::windows::window::event::processor &
		>(
			_window.awl_window_event_processor()
		)
	),
	has_focus_(
		false
	),
	focus_discover_(),
	focus_remove_(),
	cursor_discover_(),
	cursor_remove_(),
	init_message_(
		event_processor_
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			event_processor_.focus_in_callback(
				awl::window::event::focus_in_callback(
					std::bind(
						&sge::wininput::processor::on_focus_in,
						this,
						std::placeholders::_1
					)
				)
			)
		)
		(
			event_processor_.focus_out_callback(
				awl::window::event::focus_out_callback(
					std::bind(
						&sge::wininput::processor::on_focus_out,
						this,
						std::placeholders::_1
					)
				)
			)
		)
		(
			event_processor_.register_callback(
				init_message_.type(),
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::wininput::processor::on_init,
						this,
						std::placeholders::_1
					)
				}
			)
		)
	)
{
	awl::backends::windows::event::post_message(
		windows_window_.hwnd(),
		init_message_.type(),
		awl::backends::windows::event::wparam(
			0u
		),
		awl::backends::windows::event::lparam(
			0
		)
	);
}
FCPPT_PP_POP_WARNING

sge::wininput::processor::~processor()
{
}

fcppt::signal::optional_auto_connection
sge::wininput::processor::keyboard_discover_callback(
	sge::input::keyboard::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wininput::processor::keyboard_remove_callback(
	sge::input::keyboard::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wininput::processor::mouse_discover_callback(
	sge::input::mouse::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wininput::processor::mouse_remove_callback(
	sge::input::mouse::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wininput::processor::cursor_discover_callback(
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
sge::wininput::processor::cursor_remove_callback(
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
sge::wininput::processor::focus_discover_callback(
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
sge::wininput::processor::focus_remove_callback(
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
sge::wininput::processor::joypad_discover_callback(
	sge::input::joypad::discover_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

fcppt::signal::optional_auto_connection
sge::wininput::processor::joypad_remove_callback(
	sge::input::joypad::remove_callback const &
)
{
	return
		fcppt::signal::optional_auto_connection{};
}

void
sge::wininput::processor::on_focus_in(
	awl::window::event::focus_in const &
)
{
	FCPPT_LOG_DEBUG(
		sge::wininput::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("DirectInput: focus in")
	);

	has_focus_ =
		sge::wininput::has_focus(
			true
		);
}

void
sge::wininput::processor::on_focus_out(
	awl::window::event::focus_out const &
)
{
	FCPPT_LOG_DEBUG(
		sge::wininput::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("DirectInput: focus out")
	);

	has_focus_ =
		sge::wininput::has_focus(
			false
		);
}

awl::backends::windows::window::event::return_type
sge::wininput::processor::on_init(
	awl::backends::windows::window::event::object const &
)
{
	if(
		awl::window::has_focus(
			awl_system_,
			windows_window_
		)
	)
		has_focus_ =
			sge::wininput::has_focus(
				true
			);

	return
		awl::backends::windows::window::event::return_type(
			0u
		);
}
