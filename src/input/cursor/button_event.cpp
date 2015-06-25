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


#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/position.hpp>


sge::input::cursor::button_event::button_event(
	sge::input::cursor::button_code const _button_code,
	sge::input::cursor::position const _position,
	bool const _pressed
)
:
	button_code_(
		_button_code
	),
	position_(
		_position
	),
	pressed_(
		_pressed
	)
{
}

sge::input::cursor::button_code
sge::input::cursor::button_event::button_code() const
{
	return
		button_code_;
}

sge::input::cursor::position const
sge::input::cursor::button_event::position() const
{
	return
		position_;
}

bool
sge::input::cursor::button_event::pressed() const
{
	return
		pressed_;
}
