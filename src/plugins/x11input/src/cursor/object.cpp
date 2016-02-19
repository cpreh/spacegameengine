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


#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/scroll_event.hpp>
#include <sge/x11input/logger.hpp>
#include <sge/x11input/cursor/button_code.hpp>
#include <sge/x11input/cursor/entered.hpp>
#include <sge/x11input/cursor/grab.hpp>
#include <sge/x11input/cursor/make_scroll_valuators.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <sge/x11input/cursor/position.hpp>
#include <sge/x11input/cursor/query_pointer.hpp>
#include <sge/x11input/cursor/scroll_valuator.hpp>
#include <sge/x11input/device/enter_demuxer.hpp>
#include <sge/x11input/device/enter_event.hpp>
#include <sge/x11input/device/event.hpp>
#include <sge/x11input/device/leave_demuxer.hpp>
#include <sge/x11input/device/leave_event_fwd.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <sge/x11input/device/valuator/callback.hpp>
#include <sge/x11input/device/valuator/foreach.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <awl/backends/x11/cursor/object_fwd.hpp>
#include <awl/backends/x11/system/event/type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::x11input::cursor::object::object(
	sge::x11input::device::parameters const &_param,
	awl::backends::x11::cursor::object const &_cursor,
	sge::x11input::cursor::entered const _entered
)
:
	sge::input::cursor::object(),
	sge::x11input::device::object(
		_param.id()
	),
	window_(
		_param.window()
	),
	cursor_(
		_cursor
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
				sge::x11input::device::window_demuxer::callback{
					std::bind(
						&sge::x11input::cursor::object::on_motion,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_ButtonPress
				),
				_param.id(),
				sge::x11input::device::window_demuxer::callback{
					std::bind(
						&sge::x11input::cursor::object::on_button_down,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		(
			_param.enter_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_Enter
				),
				_param.id(),
				sge::x11input::device::enter_demuxer::callback{
					std::bind(
						&sge::x11input::cursor::object::on_enter,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		(
			_param.leave_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_Leave
				),
				_param.id(),
				sge::x11input::device::leave_demuxer::callback{
					std::bind(
						&sge::x11input::cursor::object::on_leave,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_ButtonRelease
				),
				_param.id(),
				sge::x11input::device::window_demuxer::callback{
					std::bind(
						&sge::x11input::cursor::object::on_button_up,
						this,
						std::placeholders::_1
					)
				}
			)
		)
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
	scroll_valuators_(
		sge::x11input::cursor::make_scroll_valuators(
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
	entered_ =
		sge::x11input::cursor::entered(
			true
		);

	this->check_grab();
}

void
sge::x11input::cursor::object::on_focus_out()
{
	entered_ =
		sge::x11input::cursor::entered(
			false
		);

	this->check_grab();
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

sge::input::cursor::optional_position
sge::x11input::cursor::object::position() const
{
	return
		position_;
}

void
sge::x11input::cursor::object::mode(
	sge::input::cursor::mode const _mode
)
{
	mode_ =
		_mode;

	this->check_grab();
}

void
sge::x11input::cursor::object::on_motion(
	sge::x11input::device::window_event const &_event
)
{
	sge::x11input::device::valuator::foreach(
		_event.get().valuators,
		sge::x11input::device::valuator::callback{
			[
				this
			](
				sge::x11input::device::valuator::index const _index,
				sge::x11input::device::valuator::value const _value
			)
			{
				fcppt::optional::maybe_void(
					fcppt::container::find_opt_mapped(
						scroll_valuators_,
						_index
					),
					[
						_value,
						this
					](
						fcppt::reference<
							sge::x11input::cursor::scroll_valuator
						> const _valuator
					)
					{
						scroll_signal_(
							sge::input::cursor::scroll_event(
								_valuator.get().code(),
								_valuator.get().update(
									_value
								)
							)
						);
					}
				);
			}
		}
	);

	this->update_position(
		_event
	);
}

void
sge::x11input::cursor::object::on_enter(
	sge::x11input::device::enter_event const &_event
)
{
	FCPPT_LOG_DEBUG(
		sge::x11input::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("XIEnter: ")
			<< _event.get().event_x
			<< FCPPT_TEXT(",")
			<< _event.get().event_y
	);

	this->update_position(
		_event
	);
}

void
sge::x11input::cursor::object::on_leave(
	sge::x11input::device::leave_event const &
)
{
	FCPPT_LOG_DEBUG(
		sge::x11input::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("XILeave")
	);

	position_ =
		sge::input::cursor::optional_position{};

	this->move_event();
}

template<
	typename Event
>
void
sge::x11input::cursor::object::update_position(
	sge::x11input::device::event<
		Event
	> const &_event
)
{
	position_ =
		sge::input::cursor::optional_position{
			sge::x11input::cursor::position(
				_event
			)
		};

	this->move_event();
}

void
sge::x11input::cursor::object::on_button_down(
	sge::x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		sge::input::cursor::button_pressed{
			true
		}
	);
}

void
sge::x11input::cursor::object::on_button_up(
	sge::x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		sge::input::cursor::button_pressed{
			false
		}
	);
}

void
sge::x11input::cursor::object::button_event(
	sge::x11input::device::window_event const &_event,
	sge::input::cursor::button_pressed const _pressed
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
			sge::x11input::cursor::position(
				_event
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
			!cursor_grab_.has_value()
			&&
			entered_.get()
		)
			cursor_grab_ =
				optional_cursor_grab_unique_ptr(
					fcppt::make_unique_ptr<
						sge::x11input::cursor::grab
					>(
						window_,
						this->id(),
						cursor_
					)
				);
		else if(
			!entered_.get()
		)
			cursor_grab_ =
				optional_cursor_grab_unique_ptr();

		return;
	case sge::input::cursor::mode::normal:
		cursor_grab_ =
			optional_cursor_grab_unique_ptr();
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
