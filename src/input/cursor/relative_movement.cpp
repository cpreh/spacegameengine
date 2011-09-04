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


#include <sge/input/cursor/relative_movement.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/relative_move_event.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>

sge::input::cursor::relative_movement::relative_movement(
	cursor::object &_cursor
)
:
	cursor_(_cursor),
	last_position_(
		cursor_.position()
	),
	relative_move_signal_(),
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	connection_(
		cursor_.move_callback(
			std::tr1::bind(
				&cursor::relative_movement::move_callback_internal,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
FCPPT_PP_POP_WARNING
{
}

sge::input::cursor::relative_movement::~relative_movement()
{
}

fcppt::signal::auto_connection
sge::input::cursor::relative_movement::relative_move_callback(
	cursor::relative_move_callback const &_callback
)
{
	return
		relative_move_signal_.connect(
			_callback
		);
}

void
sge::input::cursor::relative_movement::move_callback_internal(
	cursor::move_event const &_event
)
{
	relative_move_signal_(
		cursor::relative_move_event(
			_event.position()
			- last_position_
		)
	);

	last_position_ = _event.position();
}
