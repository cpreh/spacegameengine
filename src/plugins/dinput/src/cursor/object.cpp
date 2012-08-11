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
#include <sge/dinput/cursor/get_pos.hpp>
#include <sge/dinput/cursor/object.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <awl/backends/windows/optional_point.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/screen_to_client.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::dinput::cursor::object::object(
	awl::backends::windows::window::event::processor &_event_processor,
	awl::backends::windows::window::object &_window
)
:
	event_processor_(
		_event_processor
	),
	window_(
		_window
	),
	button_signal_(),
	move_signal_(),
	exclusive_mode_(),
	mode_(
		sge::input::cursor::mode::normal
	),
	has_focus_(
		false
	),
	connections_(
		this->make_connections()
	)
{
}

FCPPT_PP_POP_WARNING

sge::dinput::cursor::object::~object()
{
}

fcppt::signal::auto_connection
sge::dinput::cursor::object::button_callback(
	input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::cursor::object::move_callback(
	input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

sge::input::cursor::optional_position const
sge::dinput::cursor::object::position() const
{
	awl::backends::windows::optional_point const cursor_pos(
		sge::dinput::cursor::get_pos()
	);

	if(
		!cursor_pos
	)
		return sge::input::cursor::optional_position();

	awl::backends::windows::optional_point const transformed_pos(
		awl::backends::windows::window::screen_to_client(
			window_,
			*cursor_pos
		)
	);

	return
		transformed_pos
		?
			sge::input::cursor::optional_position(
				sge::input::cursor::position(
					static_cast<
						sge::input::cursor::position_unit
					>(
						transformed_pos->x
					),
					static_cast<
						sge::input::cursor::position_unit
					>(
						transformed_pos->y
					)
				)
			)
		:
			sge::input::cursor::optional_position()
		;
}

void
sge::dinput::cursor::object::mode(
	sge::input::cursor::mode::type const _mode
)
{
	mode_ = _mode;

	if(
		mode_ == sge::input::cursor::mode::normal
	)
		exclusive_mode_.reset();
	else if(
		has_focus_
	)
		this->make_grab();
}

void
sge::dinput::cursor::object::acquire()
{
	has_focus_ = true;

	if(
		mode_ == sge::input::cursor::mode::exclusive
	)
		this->make_grab();
}

void
sge::dinput::cursor::object::unacquire()
{
	has_focus_ = false;

	exclusive_mode_.reset();
}

void
sge::dinput::cursor::object::make_grab()
{
	if(
		exclusive_mode_
	)
		return;

	exclusive_mode_.take(
		fcppt::make_unique_ptr<
			sge::dinput::cursor::exclusive_mode
		>(
			fcppt::ref(
				event_processor_
			),
			fcppt::ref(
				window_
			)
		)
	);
}

awl::backends::windows::window::event::return_type
sge::dinput::cursor::object::on_move(
	awl::backends::windows::window::event::object const &_event
)
{
	move_signal_(
		sge::input::cursor::move_event(
			sge::input::cursor::optional_position(
				sge::input::cursor::position(
					LOWORD(
						_event.lparam().get()
					),
					HIWORD(
						_event.lparam().get()
					)
				)
			)
		)
	);

	return awl::backends::windows::window::event::return_type();
}

awl::backends::windows::window::event::return_type
sge::dinput::cursor::object::on_button(
	awl::backends::windows::window::event::object const &,
	sge::input::cursor::button_code::type const _code,
	bool const _down
)
{
	button_signal_(
		sge::input::cursor::button_event(
			_code,
			_down
		)
	);

	return awl::backends::windows::window::event::return_type();
}

fcppt::signal::connection_manager::container const
sge::dinput::cursor::object::make_connections()
{
	fcppt::signal::connection_manager::container ret;

	ret.push_back(
		fcppt::signal::shared_connection(
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::event::type
				>(
					WM_MOUSEMOVE
				),
				std::tr1::bind(
					&sge::dinput::cursor::object::on_move,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	);

	this->make_button_connections(
		ret,
		WM_LBUTTONDOWN,
		WM_LBUTTONUP,
		sge::input::cursor::button_code::left
	);

	this->make_button_connections(
		ret,
		WM_MBUTTONDOWN,
		WM_MBUTTONUP,
		sge::input::cursor::button_code::middle
	);

	this->make_button_connections(
		ret,
		WM_RBUTTONDOWN,
		WM_RBUTTONUP,
		sge::input::cursor::button_code::right
	);

	return ret;
}

void
sge::dinput::cursor::object::make_button_connections(
	fcppt::signal::connection_manager::container &_container,
	awl::backends::windows::event::type::value_type const _down_event,
	awl::backends::windows::event::type::value_type const _up_event,
	sge::input::cursor::button_code::type const _code
)
{
	_container.push_back(
		fcppt::signal::shared_connection(
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::event::type
				>(
					_down_event
				),
				std::tr1::bind(
					&dinput::cursor::object::on_button,
					this,
					std::tr1::placeholders::_1,
					_code,
					true
				)
			)
		)
	);

	_container.push_back(
		fcppt::signal::shared_connection(
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::event::type
				>(
					_up_event
				),
				std::tr1::bind(
					&dinput::cursor::object::on_button,
					this,
					std::tr1::placeholders::_1,
					_code,
					false
				)
			)
		)
	);
}
