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


#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/manager.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_event.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::input::cursor::manager::manager(
	sge::input::processor &_processor,
	sge::input::cursor::discover_callback const &_discover_callback,
	sge::input::cursor::remove_callback const &_remove_callback,
	sge::input::cursor::manager::button_callback const &_button_callback,
	sge::input::cursor::manager::move_callback const &_move_callback,
	sge::input::cursor::manager::scroll_callback const &_scroll_callback
)
:
	objects_(),
	discover_callback_(
		_discover_callback
	),
	remove_callback_(
		_remove_callback
	),
	button_callback_(
		_button_callback
	),
	move_callback_(
		_move_callback
	),
	scroll_callback_(
		_scroll_callback
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			_processor.cursor_discover_callback(
				std::bind(
					&sge::input::cursor::manager::discover,
					this,
					std::placeholders::_1
				)
			)
		)
		(
			_processor.cursor_remove_callback(
				std::bind(
					&sge::input::cursor::manager::remove,
					this,
					std::placeholders::_1
				)
			)
		)
		.move_container()
	)
{
}

FCPPT_PP_POP_WARNING

sge::input::cursor::manager::~manager()
{
}

sge::input::cursor::manager::object_map const &
sge::input::cursor::manager::devices() const
{
	return objects_;
}

void
sge::input::cursor::manager::discover(
	input::cursor::discover_event const &_event
)
{
	FCPPT_ASSERT_ERROR(
		objects_.insert(
			std::make_pair(
				&_event.get(),
				fcppt::assign::make_container<
					fcppt::signal::auto_connection_container
				>(
					_event.get().button_callback(
						std::bind(
							button_callback_,
							std::ref(
								_event.get()
							),
							std::placeholders::_1
						)
					)
				)
				(
					_event.get().move_callback(
						std::bind(
							move_callback_,
							std::ref(
								_event.get()
							),
							std::placeholders::_1
						)
					)
				)
				(
					_event.get().scroll_callback(
						std::bind(
							scroll_callback_,
							std::ref(
								_event.get()
							),
							std::placeholders::_1
						)
					)
				)
				.move_container()
			)
		).second
		== true
	);

	if(
		discover_callback_
	)
		discover_callback_(
			_event
		);
}

void
sge::input::cursor::manager::remove(
	sge::input::cursor::remove_event const &_event
)
{
	FCPPT_ASSERT_ERROR(
		objects_.erase(
			&_event.get()
		)
		== 1u
	);

	if(
		remove_callback_
	)
		remove_callback_(
			_event
		);
}
