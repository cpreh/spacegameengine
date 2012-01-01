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


#include <sge/dinput/cursor/object.hpp>
#include <sge/dinput/device/funcs/acquire.hpp>
#include <sge/dinput/device/funcs/set_cooperative_level.hpp>
#include <sge/dinput/device/funcs/set_data_format.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/screen_to_client.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/preprocessor/todo.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>


sge::dinput::cursor::object::object(
	awl::backends::windows::window::event::processor &_event_processor,
	awl::backends::windows::window::instance &_window,
	IDirectInputDevice8 *const _system_mouse
)
:
	event_processor_(_event_processor),
	window_(_window),
	system_mouse_(_system_mouse),
	button_signal_(),
	move_signal_(),
	acquired_(false),
	mode_(
		sge::input::cursor::mode::normal
	),
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_event_processor.register_callback(
					awl::backends::windows::event::type(
						WM_MOUSEMOVE
					),
					std::tr1::bind(
						&dinput::cursor::object::on_move,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_event_processor.register_callback(
					awl::backends::windows::event::type(
						WM_LBUTTONDOWN
					),
					std::tr1::bind(
						&dinput::cursor::object::on_button,
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
					awl::backends::windows::event::type(
						WM_LBUTTONUP
					),
					std::tr1::bind(
						&dinput::cursor::object::on_button,
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
					awl::backends::windows::event::type(
						WM_MBUTTONDOWN
					),
					std::tr1::bind(
						&dinput::cursor::object::on_button,
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
					awl::backends::windows::event::type(
						WM_MBUTTONUP
					),
					std::tr1::bind(
						&dinput::cursor::object::on_button,
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
					awl::backends::windows::event::type(
						WM_RBUTTONDOWN
					),
					std::tr1::bind(
						&dinput::cursor::object::on_button,
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
					awl::backends::windows::event::type(
						WM_RBUTTONUP
					),
					std::tr1::bind(
						&dinput::cursor::object::on_button,
						this,
						std::tr1::placeholders::_1,
						sge::input::cursor::button_code::right,
						false
					)
				)
			)
		)
	)
FCPPT_PP_POP_WARNING
{
	// TODO: this should not be here
	device::funcs::set_data_format(
		system_mouse_,
		&c_dfDIMouse
	);
}

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
	FCPPT_PP_TODO("When should this return an empty optional?")

	POINT ret;

	if(
		::GetCursorPos(
			&ret
		)
		== 0
	)
		return sge::input::cursor::optional_position();

	ret =
		awl::backends::windows::window::screen_to_client(
			window_,
			ret
		);

	return
		sge::input::cursor::optional_position(
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
			)
		);
}

void
sge::dinput::cursor::object::mode(
	input::cursor::mode::type const _mode
)
{
	mode_ = _mode;

	this->update_grab();
}

void
sge::dinput::cursor::object::acquire()
{
	acquired_ = true;

	this->update_grab();
}

void
sge::dinput::cursor::object::unacquire()
{
	acquired_ = false;

	this->update_grab();
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

void
sge::dinput::cursor::object::update_grab()
{
	system_mouse_->Unacquire();

	if(
		mode_ == sge::input::cursor::mode::exclusive
		&& acquired_
	)
		dinput::device::funcs::set_cooperative_level(
			system_mouse_,
			window_,
			DISCL_FOREGROUND | DISCL_EXCLUSIVE
		);
	else
		dinput::device::funcs::set_cooperative_level(
			system_mouse_,
			window_,
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
		);

	device::funcs::acquire(
		system_mouse_
	);
}
