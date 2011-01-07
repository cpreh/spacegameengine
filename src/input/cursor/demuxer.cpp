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


#include <sge/input/cursor/demuxer.hpp>
#include <sge/input/cursor/no_object.hpp>
#include <sge/input/cursor/object_vector.hpp>
#include <sge/input/processor.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <boost/foreach.hpp>

sge::input::cursor::demuxer::demuxer(
	input::processor_ptr const _processor
)
:
	processor_connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_processor->cursor_discover_callback(
					std::tr1::bind(
						&cursor::demuxer::discover_callback,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor->cursor_remove_callback(
					std::tr1::bind(
						&cursor::demuxer::remove_callback,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	button_signal_(),
	move_signal_(),
	cursors_(),
	cursor_connections_(),
	current_cursor_()
{
	BOOST_FOREACH(
		cursor::object_vector::value_type cursor,
		_processor->cursors()
	)
		this->discover_callback(
			cursor
		);
}

sge::input::cursor::demuxer::~demuxer()
{
}

fcppt::signal::auto_connection
sge::input::cursor::demuxer::button_callback(
	cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::cursor::demuxer::move_callback(
	cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

sge::input::cursor::position const
sge::input::cursor::demuxer::position() const
{
	return
		current_cursor()
		?
			current_cursor()->position()
		:
			throw sge::input::cursor::no_object();
}

void
sge::input::cursor::demuxer::show()
{
	if(
		current_cursor()
	)
		current_cursor()->show();
	else
		throw sge::input::cursor::no_object();
}

void
sge::input::cursor::demuxer::hide()
{
	if(
		current_cursor()
	)
		current_cursor()->hide();
	else
		throw sge::input::cursor::no_object();
}

void
sge::input::cursor::demuxer::window_mode(
	cursor::window_mode::type const _mode
)
{
	if(
		current_cursor()
	)

		current_cursor()->window_mode(
			_mode
		);
	else
		throw sge::input::cursor::no_object();
}

sge::input::cursor::object_ptr const
sge::input::cursor::demuxer::current_cursor() const
{
	return current_cursor_;
}

void
sge::input::cursor::demuxer::button_callback_internal(
	cursor::button_event const &_event
)
{
	button_signal_(
		_event
	);
}

void
sge::input::cursor::demuxer::move_callback_internal(
	cursor::move_event const &_event
)
{
	move_signal_(
		_event
	);
}

void
sge::input::cursor::demuxer::discover_callback(
	cursor::object_ptr const _object
)
{
	cursors_.insert(
		_object
	);

	if(
		!current_cursor_
	)
		this->assign_cursor(
			_object
		);
}

void
sge::input::cursor::demuxer::remove_callback(
	cursor::object_ptr const _object
)
{
	if(
		current_cursor_ != _object
	)
		return;

	if(
		cursors_.empty()
	)
	{
		current_cursor_.reset();
		
		cursor_connections_.clear();
	}
	else
		this->assign_cursor(
			*cursors_.begin() // TODO: which one to use here?
		);
}

void
sge::input::cursor::demuxer::assign_cursor(
	cursor::object_ptr const _object
)
{
	current_cursor_ = _object;

	cursor_connections_.assign(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				current_cursor_->button_callback(
					std::tr1::bind(
						&cursor::demuxer::button_callback_internal,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				current_cursor_->move_callback(
					std::tr1::bind(
						&cursor::demuxer::move_callback_internal,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	);
}
