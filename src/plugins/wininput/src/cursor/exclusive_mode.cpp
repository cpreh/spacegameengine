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


#include <sge/wininput/cursor/exclusive_mode.hpp>
#include <sge/wininput/cursor/grab.hpp>
#include <sge/wininput/cursor/ungrab.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/callback.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <thread>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::wininput::cursor::exclusive_mode::exclusive_mode(
	awl::backends::windows::window::event::processor &_event_processor,
	awl::backends::windows::window::object &_window
)
:
	grab_event_(),
	window_(
		_window
	),
	connections_(
		fcppt::algorithm::join(
			this->make_connection_pair(
				_event_processor,
				WM_ENTERSIZEMOVE,
				WM_EXITSIZEMOVE
			),
			this->make_connection_pair(
				_event_processor,
				WM_ENTERMENULOOP,
				WM_EXITMENULOOP
			)
		)
	)
{
	while(
		!sge::wininput::cursor::grab(
			window_
		)
	)
		std::this_thread::sleep_for(
			std::chrono::milliseconds(
				1
			)
		);
}

FCPPT_PP_POP_WARNING

sge::wininput::cursor::exclusive_mode::~exclusive_mode()
{
	sge::wininput::cursor::ungrab();
}

awl::backends::windows::window::event::return_type
sge::wininput::cursor::exclusive_mode::on_temp_unacquire(
	awl::backends::windows::event::type const _event_type,
	awl::backends::windows::window::event::object const &
)
{
	grab_event_ =
		optional_event_type(
			_event_type
		);

	sge::wininput::cursor::ungrab();

	return
		awl::backends::windows::window::event::return_type(
			0
		);
}

awl::backends::windows::window::event::return_type
sge::wininput::cursor::exclusive_mode::on_temp_acquire(
	awl::backends::windows::event::type const _event_type,
	awl::backends::windows::window::event::object const &
)
{
	if(
		grab_event_
		==
		optional_event_type(
			_event_type
		)
	)
		sge::wininput::cursor::grab(
			window_
		);

	grab_event_ =
		optional_event_type();

	return
		awl::backends::windows::window::event::return_type(
			0
		);
}

fcppt::signal::auto_connection_container
sge::wininput::cursor::exclusive_mode::make_connection_pair(
	awl::backends::windows::window::event::processor &_event_processor,
	awl::backends::windows::event::type::value_type const _enter_event,
	awl::backends::windows::event::type::value_type const _exit_event
)
{
	awl::backends::windows::event::type const exit_event(
		_exit_event
	);

	return
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			_event_processor.register_callback(
				awl::backends::windows::event::type{
					_enter_event
				},
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::wininput::cursor::exclusive_mode::on_temp_unacquire,
						this,
						exit_event,
						std::placeholders::_1
					)
				}
			)
		)(
			_event_processor.register_callback(
				exit_event,
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::wininput::cursor::exclusive_mode::on_temp_acquire,
						this,
						exit_event,
						std::placeholders::_1
					)
				}
			)
		).move_container();
}
