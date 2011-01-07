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


#include <sge/systems/input.hpp>

sge::systems::input::input(
	systems::input_helper_field const &_input_helpers,
	systems::cursor_grab::type const _cursor_grab
)
:
	input_helpers_(_input_helpers),
	cursor_grab_(_cursor_grab)
{}

sge::systems::input_helper_field const &
sge::systems::input::input_helpers() const
{
	return input_helpers_;
}

sge::systems::cursor_grab::type
sge::systems::input::cursor_grab() const
{
	return cursor_grab_;
}
