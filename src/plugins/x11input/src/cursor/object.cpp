/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/input/cursor/scroll_event.hpp>
#include <sge/x11input/cursor/button_code.hpp>
#include <sge/x11input/cursor/grab.hpp>
#include <sge/x11input/cursor/make_info.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <sge/x11input/cursor/query_pointer.hpp>
#include <sge/x11input/cursor/scroll_valuator_map.hpp>
#include <sge/x11input/cursor/scroll_value.hpp>
#include <sge/x11input/device/foreach_valuator.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/valuator_index.hpp>
#include <sge/x11input/device/valuator_value.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::x11input::cursor::object::object(
	sge::x11input::device::parameters const &_param,
	sge::x11input::cursor::image const _invisible_image,
	bool const _entered
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
			fcppt::signal::auto_connection_container
		>(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_Motion
				),
				_param.id(),
				std::bind(
					&sge::x11input::cursor::object::on_motion,
					this,
					std::placeholders::_1
				)
			)
		)
		(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_ButtonPress
				),
				_param.id(),
				std::bind(
					&sge::x11input::cursor::object::on_button_down,
					this,
					std::placeholders::_1
				)
			)
		)
		(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_ButtonRelease
				),
				_param.id(),
				std::bind(
					&sge::x11input::cursor::object::on_button_up,
					this,
					std::placeholders::_1
				)
			)
		)
		.move_container()
	),
	mode_(
		sge::input::cursor::mode::normal
	),
	entered_(
		_entered
	),
	position_(
		sge::x11input::cursor::query_pointer(
			window_,
			_param.id()
		)
	),
	info_(
		sge::x11input::cursor::make_info(
			_param.info()
		)
	),
	button_signal_(),
	move_signal_(),
	scroll_signal_(),
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
	sge::input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::cursor::object::move_callback(
	sge::input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::cursor::object::scroll_callback(
	sge::input::cursor::scroll_callback const &_callback
)
{
	return
		scroll_signal_.connect(
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
	sge::input::cursor::mode const _mode
)
{
	mode_ = _mode;

	this->check_grab();
}

void
sge::x11input::cursor::object::on_motion(
	sge::x11input::device::window_event const &_event
)
{
	sge::x11input::device::foreach_valuator(
		_event.get().valuators,
		std::bind(
			&sge::x11input::cursor::object::process_valuator,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	);

	sge::input::cursor::position const new_position(
		fcppt::cast::float_to_int<
			sge::input::cursor::position_unit
		>(
			_event.get().event_x
		),
		fcppt::cast::float_to_int<
			sge::input::cursor::position_unit
		>(
			_event.get().event_y
		)
	);

	if(
		position_
		&&
		new_position
		==
		*position_
	)
		return;

	position_ =
		new_position;

	this->move_event();
}

void
sge::x11input::cursor::object::process_valuator(
	sge::x11input::device::valuator_index const _index,
	sge::x11input::device::valuator_value const _value
)
{
	sge::x11input::cursor::scroll_valuator_map &scroll_valuators(
		info_.scroll_valuators()
	);

	sge::x11input::cursor::scroll_valuator_map::iterator const it(
		scroll_valuators.find(
			_index
		)
	);

	if(
		it == scroll_valuators.end()
	)
		return;

	sge::x11input::device::valuator_value const delta(
		_value
		-
		it->second.last_value()
	);

	it->second.last_value(
		_value
	);

	scroll_signal_(
		sge::input::cursor::scroll_event(
			it->second.code(),
			sge::x11input::cursor::scroll_value(
				delta
			)
		)
	);
}

void
sge::x11input::cursor::object::on_button_down(
	sge::x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		true
	);
}

void
sge::x11input::cursor::object::on_button_up(
	sge::x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		false
	);
}

void
sge::x11input::cursor::object::button_event(
	sge::x11input::device::window_event const &_event,
	bool const _pressed
)
{
	if(
		_event.get().flags
		&
		XIPointerEmulated
	)
		return;

	button_signal_(
		sge::input::cursor::button_event(
			sge::x11input::cursor::button_code(
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
		sge::input::cursor::move_event(
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
	case sge::input::cursor::mode::exclusive:
		if(
			!cursor_grab_
			&& entered_
		)
			cursor_grab_ =
				fcppt::make_unique_ptr<
					sge::x11input::cursor::grab
				>(
					window_,
					this->id(),
					invisible_image_
				);
		else if(
			!entered_
		)
			cursor_grab_.reset();

		return;
	case sge::input::cursor::mode::normal:
		cursor_grab_.reset();
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
