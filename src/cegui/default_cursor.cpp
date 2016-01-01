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


#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_event_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::cegui::default_cursor::default_cursor(
	sge::cegui::syringe &_syringe,
	sge::input::cursor::object &_cursor
)
:
	syringe_(
		_syringe
	),
	button_connection_(
		_cursor.button_callback(
			sge::input::cursor::button_callback{
				std::bind(
					&default_cursor::button_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	move_connection_(
		_cursor.move_callback(
			sge::input::cursor::move_callback{
				std::bind(
					&default_cursor::move_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	scroll_connection_(
		_cursor.scroll_callback(
			sge::input::cursor::scroll_callback{
				std::bind(
					&default_cursor::scroll_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
	fcppt::optional::maybe_void(
		_cursor.position(),
		[
			this
		](
			sge::input::cursor::position const _pos
		)
		{
			syringe_.inject(
				_pos
			);
		}
	);
}

FCPPT_PP_POP_WARNING

sge::cegui::default_cursor::~default_cursor()
{
}

void
sge::cegui::default_cursor::button_callback(
	sge::input::cursor::button_event const &_event
)
{
	syringe_.inject(
		_event
	);
}

void
sge::cegui::default_cursor::move_callback(
	sge::input::cursor::move_event const &_event
)
{
	syringe_.inject(
		_event
	);
}

void
sge::cegui::default_cursor::scroll_callback(
	sge::input::cursor::scroll_event const &_event
)
{
	syringe_.inject(
		_event
	);
}
