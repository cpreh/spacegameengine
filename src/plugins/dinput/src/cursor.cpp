/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../cursor.hpp"
#include "../cursor_confine.hpp"
#include "../cursor_define.hpp"
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/input/cursor/window_mode.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/screen_to_client.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>

sge::dinput::cursor::cursor(
	awl::backends::windows::window::event::processor &_event_processor,
	awl::backends::windows::window::instance &_window
)
:
	event_processor_(_event_processor),
	window_(_window),
	cursor_define_(),
	cursor_confine_(),
	button_signal_(),
	move_signal_(),
	acquired_(false),
	window_mode_(
		sge::input::cursor::window_mode::move_freely
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_event_processor.register_callback(
					WM_MOUSEMOVE,
					std::tr1::bind(
						&dinput::cursor::on_move,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_event_processor.register_callback(
					WM_LBUTTONDOWN,
					std::tr1::bind(
						&dinput::cursor::on_button,
						this,
						std::tr1::placeholders::_1,
						sge::input::cursor::button_code::left,
						true
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_event_processor.register_callback(
					WM_LBUTTONUP,
					std::tr1::bind(
						&dinput::cursor::on_button,
						this,
						std::tr1::placeholders::_1,
						sge::input::cursor::button_code::left,
						false
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_event_processor.register_callback(
					WM_MBUTTONDOWN,
					std::tr1::bind(
						&dinput::cursor::on_button,
						this,
						std::tr1::placeholders::_1,
						sge::input::cursor::button_code::middle,
						true
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_event_processor.register_callback(
					WM_MBUTTONUP,
					std::tr1::bind(
						&dinput::cursor::on_button,
						this,
						std::tr1::placeholders::_1,
						sge::input::cursor::button_code::middle,
						false
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_event_processor.register_callback(
					WM_RBUTTONDOWN,
					std::tr1::bind(
						&dinput::cursor::on_button,
						this,
						std::tr1::placeholders::_1,
						sge::input::cursor::button_code::right,
						true
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_event_processor.register_callback(
					WM_RBUTTONUP,
					std::tr1::bind(
						&dinput::cursor::on_button,
						this,
						std::tr1::placeholders::_1,
						sge::input::cursor::button_code::right,
						false
					)
				)
			)
		)
	)
{
}

sge::dinput::cursor::~cursor()
{
}

fcppt::signal::auto_connection
sge::dinput::cursor::button_callback(
	input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::cursor::move_callback(
	input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

sge::input::cursor::position const
sge::dinput::cursor::position() const
{
	POINT ret;

	if(
		::GetCursorPos(
			&ret
		)
		== 0
	)
		throw sge::input::exception(
			FCPPT_TEXT("GetCursorPos() failed!")
		);

	ret =
		awl::backends::windows::window::screen_to_client(
			window_,
			ret
		);

	return
		sge::input::cursor::position(
			static_cast<
				sge::input::cursor::position_unit
			>(
				ret.x
			),
			static_cast<
				sge::input::cursor::position_unit
			>(
				ret.y
			)
		);
}

void
sge::dinput::cursor::visibility(
	bool const _value
)
{
	if(
		_value == !cursor_define_
	)
		return;

	if(
		_value
	)
		cursor_define_.reset();
	else
		cursor_define_.take(
			fcppt::make_unique_ptr<
				dinput::cursor_define
			>(
				fcppt::ref(
					event_processor_
				)
			)
		);
}

void
sge::dinput::cursor::window_mode(
	input::cursor::window_mode::type const _mode
)
{
	window_mode_ = _mode;

	this->update_confine();
}

void
sge::dinput::cursor::acquire()
{
	acquired_ = true;

	this->update_confine();
}

void
sge::dinput::cursor::unacquire()
{
	acquired_ = false;

	this->update_confine();
}

awl::backends::windows::window::event::return_type
sge::dinput::cursor::on_move(
	awl::backends::windows::window::event::object const &_event
)
{
	move_signal_(
		sge::input::cursor::move_event(
			sge::input::cursor::position(
				LOWORD(
					_event.lparam()
				),
				HIWORD(
					_event.lparam()
				)
			)
		)
	);

	return awl::backends::windows::window::event::return_type();
}

awl::backends::windows::window::event::return_type
sge::dinput::cursor::on_button(
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

void
sge::dinput::cursor::update_confine()
{
	if(
		window_mode_ == sge::input::cursor::window_mode::confine
		&& acquired_
	)
	{
		if(
			!cursor_confine_
		)
			cursor_confine_.take(
				fcppt::make_unique_ptr<
					dinput::cursor_confine
				>(
					fcppt::ref(
						window_
					)
				)
			);
	}
	else
		cursor_confine_.reset();
}
