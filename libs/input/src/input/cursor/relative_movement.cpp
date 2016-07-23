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


#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/relative_move_callback.hpp>
#include <sge/input/cursor/relative_move_event.hpp>
#include <sge/input/cursor/relative_movement.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::input::cursor::relative_movement::relative_movement(
	sge::input::cursor::object &_cursor
)
:
	cursor_(
		_cursor
	),
	last_position_(
		cursor_.position()
	),
	relative_move_signal_(),
	connection_(
		cursor_.move_callback(
			sge::input::cursor::move_callback(
				std::bind(
					&sge::input::cursor::relative_movement::move_callback_internal,
					this,
					std::placeholders::_1
				)
			)
		)
	)
{
}
FCPPT_PP_POP_WARNING

sge::input::cursor::relative_movement::~relative_movement()
{
}

fcppt::signal::auto_connection
sge::input::cursor::relative_movement::relative_move_callback(
	sge::input::cursor::relative_move_callback const &_callback
)
{
	return
		relative_move_signal_.connect(
			_callback
		);
}

void
sge::input::cursor::relative_movement::move_callback_internal(
	sge::input::cursor::move_event const &_event
)
{
	auto const assign_position(
		[
			this,
			&_event
		]{
			last_position_ =
				_event.position();
		}
	);

	fcppt::optional::maybe(
		last_position_,
		assign_position,
		[
			this,
			&assign_position,
			&_event
		](
			sge::input::cursor::position const _last_position
		)
		{
			fcppt::optional::maybe(
				_event.position(),
				assign_position,
				[
					this,
					&assign_position,
					_last_position
				](
					sge::input::cursor::position const _new_position
				)
				{
					relative_move_signal_(
						sge::input::cursor::relative_move_event(
							_new_position
							-
							_last_position
						)
					);

					assign_position();
				}
			);
		}
	);
}
