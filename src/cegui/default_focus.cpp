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


#include <sge/cegui/default_focus.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/char_event_fwd.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event_fwd.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/key_repeat_event_fwd.hpp>
#include <sge/input/focus/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::cegui::default_focus::default_focus(
	sge::cegui::syringe &_syringe,
	sge::input::focus::object &_focus
)
:
	syringe_(
		_syringe
	),
	key_callback_(
		_focus.key_callback(
			sge::input::focus::key_callback{
				std::bind(
					&default_focus::key_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	key_repeat_callback_(
		_focus.key_repeat_callback(
			sge::input::focus::key_repeat_callback{
				std::bind(
					&default_focus::key_repeat_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	char_callback_(
		_focus.char_callback(
			sge::input::focus::char_callback{
				std::bind(
					&default_focus::char_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}

sge::cegui::default_focus::~default_focus()
{
}

void
sge::cegui::default_focus::key_callback(
	sge::input::focus::key_event const &_event
)
{
	syringe_.inject(
		_event
	);
}

void
sge::cegui::default_focus::key_repeat_callback(
	sge::input::focus::key_repeat_event const &_event
)
{
	syringe_.inject(
		_event
	);
}

void
sge::cegui::default_focus::char_callback(
	sge::input::focus::char_event const &_event
)
{
	syringe_.inject(
		_event
	);
}
