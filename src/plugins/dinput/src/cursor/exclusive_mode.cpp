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


#include <sge/dinput/cursor/exclusive_mode.hpp>
#include <sge/dinput/cursor/grab.hpp>
#include <sge/dinput/cursor/ungrab.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/time/sleep_any.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::dinput::cursor::exclusive_mode::exclusive_mode(
	awl::backends::windows::window::event::processor &_event_processor,
	awl::backends::windows::window::object &_window
)
:
	grab_event_(),
	window_(
		_window
	),
	connections_(
		this->make_connections(
			_event_processor
		)
	)
{
	while(
		!sge::dinput::cursor::grab(
			window_
		)
	)
		fcppt::time::sleep_any(
			boost::chrono::milliseconds(
				1
			)
		);
}

FCPPT_PP_POP_WARNING

sge::dinput::cursor::exclusive_mode::~exclusive_mode()
{
	sge::dinput::cursor::ungrab();
}

awl::backends::windows::window::event::return_type
sge::dinput::cursor::exclusive_mode::on_temp_unacquire(
	awl::backends::windows::event::type const _event_type,
	awl::backends::windows::window::event::object const &
)
{
	grab_event_ =
		_event_type;

	sge::dinput::cursor::ungrab();

	return
		awl::backends::windows::window::event::return_type(
			0
		);
}

awl::backends::windows::window::event::return_type
sge::dinput::cursor::exclusive_mode::on_temp_acquire(
	awl::backends::windows::event::type const _event_type,
	awl::backends::windows::window::event::object const &
)
{
	if(
		grab_event_
		&&
		*grab_event_
		==
		_event_type
	)
		sge::dinput::cursor::grab(
			window_
		);

	grab_event_.reset();

	return
		awl::backends::windows::window::event::return_type(
			0
		);
}

fcppt::signal::connection_manager::container const
sge::dinput::cursor::exclusive_mode::make_connections(
	awl::backends::windows::window::event::processor &_event_processor
)
{
	fcppt::signal::connection_manager::container ret;

	this->make_connection_pair(
		ret,
		_event_processor,
		WM_ENTERSIZEMOVE,
		WM_EXITSIZEMOVE
	);

	this->make_connection_pair(
		ret,
		_event_processor,
		WM_ENTERMENULOOP,
		WM_EXITMENULOOP
	);

	return ret;
}

void
sge::dinput::cursor::exclusive_mode::make_connection_pair(
	fcppt::signal::connection_manager::container &_container,
	awl::backends::windows::window::event::processor &_event_processor,
	awl::backends::windows::event::type::value_type const _enter_event,
	awl::backends::windows::event::type::value_type const _exit_event
)
{
	awl::backends::windows::event::type const exit_event(
		fcppt::strong_typedef_construct_cast<
			awl::backends::windows::event::type
		>(
			_exit_event
		)
	);

	_container.push_back(
		fcppt::signal::shared_connection(
			_event_processor.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::event::type
				>(
					_enter_event
				),
				std::tr1::bind(
					&sge::dinput::cursor::exclusive_mode::on_temp_unacquire,
					this,
					exit_event,
					std::tr1::placeholders::_1
				)
			)
		)
	);

	_container.push_back(
		fcppt::signal::shared_connection(
			_event_processor.register_callback(
				exit_event,
				std::tr1::bind(
					&sge::dinput::cursor::exclusive_mode::on_temp_acquire,
					this,
					exit_event,
					std::tr1::placeholders::_1
				)
			)
		)
	);
}
