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


#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/x11input/cursor/button_code.hpp>
#include <sge/x11input/cursor/grab.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <sge/x11input/cursor/query_pointer.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::cursor::object::object(
	x11input::device::parameters const &_param,
	cursor::image const _invisible_image
)
:
	sge::input::cursor::object(),
	sge::x11input::device::object(
		_param.id()
	),
	window_(
		_param.window()
	),
	invisible_image_(
		_invisible_image
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
	mode_(
		sge::input::cursor::mode::normal
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
	cursor_grab_()
{
}

sge::x11input::cursor::object::~object()
{
}

void
sge::x11input::cursor::object::on_focus_in()
{
	entered_ = true;

	this->check_grab();
}

void
sge::x11input::cursor::object::on_focus_out()
{
	entered_ = false;

	this->check_grab();
}

void
sge::x11input::cursor::object::on_leave()
{
	position_.reset();

	this->move_event();
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

sge::input::cursor::optional_position const
sge::x11input::cursor::object::position() const
{
	return position_;
}

void
sge::x11input::cursor::object::mode(
	input::cursor::mode::type const _mode
)
{
	mode_ = _mode;

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

	this->move_event();
}

void
sge::x11input::cursor::object::on_button_down(
	x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		true
	);
}

void
sge::x11input::cursor::object::on_button_up(
	x11input::device::window_event const &_event
)
{
	this->button_event(
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
sge::x11input::cursor::object::move_event()
{
	move_signal_(
		input::cursor::move_event(
			position_
		)
	);
}

void
sge::x11input::cursor::object::check_grab()
{
	switch(
		mode_
	)
	{
	case input::cursor::mode::exclusive:
		if(
			!cursor_grab_
			&& entered_
		)
			cursor_grab_.take(
				fcppt::make_unique_ptr<
					cursor::grab
				>(
					fcppt::ref(
						window_
					),
					this->id(),
					invisible_image_
				)
			);
		else if(
			!entered_
		)
			cursor_grab_.reset();

		return;
	case input::cursor::mode::normal:
		cursor_grab_.reset();
		return;
	case input::cursor::mode::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
