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


#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/wininput/cursor/exclusive_mode.hpp>
#include <sge/wininput/cursor/grab.hpp>
#include <sge/wininput/cursor/ungrab.hpp>
#include <awl/backends/windows/message_type.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/generic.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <thread>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::wininput::cursor::exclusive_mode::exclusive_mode(
	sge::window::object &_sge_window,
	awl::backends::windows::window::object &_window
)
:
	grab_event_{},
	window_{
		_window
	},
	event_connection_{
		_sge_window.event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				{
					return
						this->on_event(
							_event
						);
				}
			}
		)
	}
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

awl::event::container
sge::wininput::cursor::exclusive_mode::on_event(
	awl::window::event::base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic<
			awl::backends::windows::window::event::generic const
		>(
			_event
		),
		[
			this
		](
			fcppt::reference<
				awl::backends::windows::window::event::generic const
			> const _window_event
		)
		{
			this->on_window_event(
				_window_event.get()
			);
		}
	);

	return
		awl::event::container{};
}

void
sge::wininput::cursor::exclusive_mode::on_window_event(
	awl::backends::windows::window::event::generic const &_event
)
{
	switch(
		_event.type().get()
	)
	{
	case WM_ENTERSIZEMOVE:
	case WM_ENTERMENULOOP:
		this->on_temp_unacquire(
			_event.type()
		);

		break;
	case WM_EXITSIZEMOVE:
	case WM_EXITMENULOOP:
		this->on_temp_acquire(
			_event.type()
		);
		break;
	}
}

void
sge::wininput::cursor::exclusive_mode::on_temp_unacquire(
	awl::backends::windows::message_type const _event_type
)
{
	grab_event_ =
		optional_event_type(
			_event_type
		);

	sge::wininput::cursor::ungrab();
}

void
sge::wininput::cursor::exclusive_mode::on_temp_acquire(
	awl::backends::windows::message_type const _event_type
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
}
