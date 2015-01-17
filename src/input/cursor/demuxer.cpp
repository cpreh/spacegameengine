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


#include <sge/input/processor.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/choose_callback.hpp>
#include <sge/input/cursor/demuxer.hpp>
#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/no_object.hpp>
#include <sge/input/cursor/optional_object_ref.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/remove_event.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_event_fwd.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::input::cursor::demuxer::demuxer(
	sge::input::processor &_processor,
	sge::input::cursor::choose_callback const &_choose
)
:
	choose_(
		_choose
	),
	processor_connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			_processor.cursor_discover_callback(
				std::bind(
					&sge::input::cursor::demuxer::discover_callback,
					this,
					std::placeholders::_1
				)
			)
		)
		(
			_processor.cursor_remove_callback(
				std::bind(
					&sge::input::cursor::demuxer::remove_callback,
					this,
					std::placeholders::_1
				)
			)
		)
		.move_container()
	),
	button_signal_(),
	move_signal_(),
	scroll_signal_(),
	cursors_(),
	cursor_connections_(),
	current_cursor_()
{
}
FCPPT_PP_POP_WARNING

sge::input::cursor::demuxer::~demuxer()
{
}

fcppt::signal::auto_connection
sge::input::cursor::demuxer::button_callback(
	sge::input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::cursor::demuxer::move_callback(
	sge::input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::cursor::demuxer::scroll_callback(
	sge::input::cursor::scroll_callback const &_callback
)
{
	return
		scroll_signal_.connect(
			_callback
		);
}

sge::input::cursor::optional_position const
sge::input::cursor::demuxer::position() const
{
	return
		this->current_cursor()
		?
			this->current_cursor()->position()
		:
			sge::input::cursor::optional_position();
}

void
sge::input::cursor::demuxer::mode(
	sge::input::cursor::mode const _mode
)
{
	if(
		this->current_cursor()
	)
		this->current_cursor()->mode(
			_mode
		);
	else
		throw sge::input::cursor::no_object();
}

sge::input::cursor::optional_object_ref const
sge::input::cursor::demuxer::current_cursor() const
{
	return current_cursor_;
}

void
sge::input::cursor::demuxer::button_callback_internal(
	sge::input::cursor::button_event const &_event
)
{
	button_signal_(
		_event
	);
}

void
sge::input::cursor::demuxer::move_callback_internal(
	sge::input::cursor::move_event const &_event
)
{
	move_signal_(
		_event
	);
}

void
sge::input::cursor::demuxer::scroll_callback_internal(
	sge::input::cursor::scroll_event const &_event
)
{
	scroll_signal_(
		_event
	);
}

void
sge::input::cursor::demuxer::discover_callback(
	sge::input::cursor::discover_event const &_event
)
{
	FCPPT_ASSERT_ERROR(
		cursors_.insert(
			&_event.get()
		).second
	);

	this->assign_cursor();
}

void
sge::input::cursor::demuxer::remove_callback(
	sge::input::cursor::remove_event const &_event
)
{
	cursors_.erase(
		&_event.get()
	);

	this->assign_cursor();
}

void
sge::input::cursor::demuxer::assign_cursor()
{
	current_cursor_ =
		choose_(
			cursors_
		);

	if(
		!current_cursor_
	)
	{
		cursor_connections_.clear();

		return;
	}

	cursor_connections_ =
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			current_cursor_->button_callback(
				std::bind(
					&sge::input::cursor::demuxer::button_callback_internal,
					this,
					std::placeholders::_1
				)
			)
		)
		(
			current_cursor_->move_callback(
				std::bind(
					&sge::input::cursor::demuxer::move_callback_internal,
					this,
					std::placeholders::_1
				)
			)
		)
		(
			current_cursor_->scroll_callback(
				std::bind(
					&sge::input::cursor::demuxer::scroll_callback_internal,
					this,
					std::placeholders::_1
				)
			)
		);

	move_signal_(
		sge::input::cursor::move_event(
			this->position()
		)
	);
}
