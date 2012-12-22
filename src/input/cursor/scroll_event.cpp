/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_event.hpp>
#include <sge/input/cursor/scroll_value.hpp>


sge::input::cursor::scroll_event::scroll_event(
	sge::input::cursor::scroll_code const _code,
	sge::input::cursor::scroll_value const _value
)
:
	code_(
		_code
	),
	value_(
		_value
	)
{
}

sge::input::cursor::scroll_code
sge::input::cursor::scroll_event::code() const
{
	return code_;
}

sge::input::cursor::scroll_value
sge::input::cursor::scroll_event::value() const
{
	return value_;
}
