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


#include "../object.hpp"
#include "../button_code.hpp"
#include "../confine.hpp"
#include "../create_confine.hpp"
#include "../define.hpp"
#include "../query_pointer.hpp"
#include "../../device/parameters.hpp"
#include "../../device/window_demuxer.hpp"
#include "../../device/window_event.hpp"
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <X11/extensions/XInput2.h>
#include <X11/Xlib.h>

sge::x11input::cursor::object::object(
	x11input::device::parameters const &_param
)
:
	sge::input::cursor::object(),
	sge::x11input::device::object(
		_param.id()
	),
	window_(
		_param.window()
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_param.window_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_Motion
					),
					_param.id(),
					std::tr1::bind(
						&object::on_motion,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_param.window_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_ButtonPress
					),
					_param.id(),
					std::tr1::bind(
						&object::on_button_down,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_param.window_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_ButtonRelease
					),
					_param.id(),
					std::tr1::bind(
						&object::on_button_up,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	window_mode_(
		sge::input::cursor::window_mode::move_freely
	),
	entered_(
		false
	),
	position_(
		x11input::cursor::query_pointer(
			window_,
			_param.id()
		)
	),
	button_signal_(),
	move_signal_(),
	cursor_confine_(),
	cursor_define_()
{
}

sge::x11input::cursor::object::~object()
{
}

void
sge::x11input::cursor::object::on_enter()
{
	entered_ = true;

	this->check_grab();
}

void
sge::x11input::cursor::object::on_leave()
{
	entered_ = false;

	this->check_grab();
}

fcppt::signal::auto_connection
sge::x11input::cursor::object::button_callback(
	input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::cursor::object::move_callback(
	input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

sge::input::cursor::position const
sge::x11input::cursor::object::position() const
{
	return position_;
}

void
sge::x11input::cursor::object::visibility(
	bool const _value
)
{
	if(
		!_value && cursor_define_
	)
		return;
	
	if(
		_value
	)
		cursor_define_.reset();
	else
		cursor_define_.take(
			fcppt::make_unique_ptr<
				x11input::cursor::define
			>(
				fcppt::ref(
					window_
				),
				this->id()
			)
		);
}

void
sge::x11input::cursor::object::window_mode(
	input::cursor::window_mode::type const _mode
)
{
	window_mode_ = _mode;

	this->check_grab();
}

void
sge::x11input::cursor::object::on_motion(
	x11input::device::window_event const &_event
)
{
	position_ = 
		input::cursor::position(
			static_cast<
				input::cursor::position_unit
			>(
				_event.get().event_x
			),
			static_cast<
				input::cursor::position_unit
			>(
				_event.get().event_y
			)
		);
	
	move_signal_(
		input::cursor::move_event(
			position_
		)
	);
}

void
sge::x11input::cursor::object::on_button_down(
	x11input::device::window_event const &_event
)
{
	button_event(
		_event,
		true
	);
}

void
sge::x11input::cursor::object::on_button_up(
	x11input::device::window_event const &_event
)
{
	button_event(
		_event,
		false
	);
}

void
sge::x11input::cursor::object::button_event(
	x11input::device::window_event const &_event,
	bool const _pressed
)
{
	button_signal_(
		input::cursor::button_event(
			x11input::cursor::button_code(
				_event.get().detail
			),
			_pressed
		)
	);
}

void
sge::x11input::cursor::object::check_grab()
{
	switch(
		window_mode_
	)
	{
	case input::cursor::window_mode::confine:
		if(
			!cursor_confine_
			&& entered_
		)
			cursor_confine_.take(
				x11input::cursor::create_confine(
					window_,
					this->id()
				)
			);
		else if(
			!entered_
		)
			cursor_confine_.reset();

		return;
	case input::cursor::window_mode::move_freely:
		cursor_confine_.reset();
		return;
	case input::cursor::window_mode::size:
		break;
	}

	throw sge::input::exception(
		FCPPT_TEXT("Invalid cursor::window_mode!")
	);
}
