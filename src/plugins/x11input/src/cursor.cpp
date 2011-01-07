/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../cursor_button_code.hpp"
#include "../cursor_confine.hpp"
#include "../device/parameters.hpp"
#include "../device/window_demuxer.hpp"
#include "../device/window_event.hpp"
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/input/exception.hpp>
#include <sge/log/global.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <awl/backends/x11/window/event/processor.hpp>
#include <X11/extensions/XInput2.h>
#include <X11/Xlib.h>

sge::x11input::cursor::cursor(
	x11input::device::parameters const &_param,
	awl::backends::x11::window::event::processor_ptr const _event_processor
)
:
	device_id_(
		_param.id()
	),
	window_(
		_param.window()
	),
	event_processor_(
		_event_processor
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
						&cursor::on_motion,
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
						&cursor::on_button_down,
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
						&cursor::on_button_up,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	window_connections_(
		event_processor_
		?
			fcppt::assign::make_container<
				fcppt::signal::connection_manager::container
			>(
				fcppt::signal::shared_connection(
					event_processor_->register_callback(
						FocusIn,
						std::tr1::bind(
							&cursor::on_enter,
							this,
							std::tr1::placeholders::_1
						)
					)
				)
			)
			(
				fcppt::signal::shared_connection(
					event_processor_->register_callback(
						FocusOut,
						std::tr1::bind(
							&cursor::on_leave,
							this,
							std::tr1::placeholders::_1
						)
					)
				)
			).container()
		:
			fcppt::signal::connection_manager::container()
	),
	window_mode_(
		sge::input::cursor::window_mode::move_freely
	),
	entered_(
		false
	),
	position_(
		// TODO!
	),
	button_signal_(),
	move_signal_()
{
}

sge::x11input::cursor::~cursor()
{
}

fcppt::signal::auto_connection
sge::x11input::cursor::button_callback(
	input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::cursor::move_callback(
	input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

sge::input::cursor::position const
sge::x11input::cursor::position() const
{
	return position_;
}

void
sge::x11input::cursor::show()
{
}

void
sge::x11input::cursor::hide()
{
}

void
sge::x11input::cursor::window_mode(
	input::cursor::window_mode::type const _mode
)
{
	window_mode_ = _mode;

	this->check_grab();
}

void
sge::x11input::cursor::on_motion(
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
sge::x11input::cursor::on_button_down(
	x11input::device::window_event const &_event
)
{
	button_event(
		_event,
		true
	);
}

void
sge::x11input::cursor::on_button_up(
	x11input::device::window_event const &_event
)
{
	button_event(
		_event,
		false
	);
}

void
sge::x11input::cursor::button_event(
	x11input::device::window_event const &_event,
	bool const _pressed
)
{
	button_signal_(
		input::cursor::button_event(
			x11input::cursor_button_code(
				_event.get().detail
			),
			_pressed
		)
	);
}

void
sge::x11input::cursor::on_enter(
	awl::backends::x11::window::event::object const &
)
{
	entered_ = true;

	this->check_grab();
}

void
sge::x11input::cursor::on_leave(
	awl::backends::x11::window::event::object const &
)
{
	entered_ = false;

	this->check_grab();
}

void
sge::x11input::cursor::check_grab()
{
	if(
		!event_processor_
	)
	{
		FCPPT_LOG_ERROR(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Tried to confine a cursor that doesn't support it.")
				<< FCPPT_TEXT(" XI2 currently doesn't allow cursor confinement so ")
				<< FCPPT_TEXT(" it is only supported for the master cursor.")
		);

		return;
	}

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
				fcppt::make_unique_ptr<
					x11input::cursor_confine
				>(
					window_,
					device_id_
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
