/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/cursor/activatable.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_event_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::input::cursor::activatable::activatable(
	sge::input::cursor::object &_cursor
)
:
	sge::input::cursor::object(),
	cursor_(
		_cursor
	),
	active_(
		false
	),
	button_signal_(),
	move_signal_(),
	scroll_signal_(),
	button_connection_(
		cursor_.button_callback(
			sge::input::cursor::button_callback{
				std::bind(
					&sge::input::cursor::activatable::on_button,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	move_connection_(
		cursor_.move_callback(
			sge::input::cursor::move_callback{
				std::bind(
					&sge::input::cursor::activatable::on_move,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	scroll_connection_(
		cursor_.scroll_callback(
			sge::input::cursor::scroll_callback{
				std::bind(
					&sge::input::cursor::activatable::on_scroll,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}

sge::input::cursor::activatable::~activatable()
{
}

fcppt::signal::auto_connection
sge::input::cursor::activatable::button_callback(
	sge::input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::cursor::activatable::move_callback(
	sge::input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::cursor::activatable::scroll_callback(
	sge::input::cursor::scroll_callback const &_callback
)
{
	return
		scroll_signal_.connect(
			_callback
		);
}

sge::input::cursor::optional_position const
sge::input::cursor::activatable::position() const
{
	return
		active_
		?
			cursor_.position()
		:
			sge::input::cursor::optional_position()
		;
}

void
sge::input::cursor::activatable::mode(
	sge::input::cursor::mode const _mode
)
{
	cursor_.mode(
		_mode
	);
}

void
sge::input::cursor::activatable::active(
	bool const _active
)
{
	active_ =
		_active;
}

bool
sge::input::cursor::activatable::active() const
{
	return
		active_;
}

void
sge::input::cursor::activatable::on_button(
	sge::input::cursor::button_event const &_event
)
{
	if(
		active_
	)
		button_signal_(
			_event
		);
}

void
sge::input::cursor::activatable::on_move(
	sge::input::cursor::move_event const &_event
)
{
	if(
		active_
	)
		move_signal_(
			_event
		);
}

void
sge::input::cursor::activatable::on_scroll(
	sge::input::cursor::scroll_event const &_event
)
{
	if(
		active_
	)
		scroll_signal_(
			_event
		);
}
