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


#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper_field.hpp>


sge::systems::input::input(
	systems::input_helper_field const &_input_helpers,
	systems::cursor_option_field const &_cursor_options
)
:
	input_helpers_(_input_helpers),
	cursor_options_(_cursor_options)
{
}

sge::systems::input_helper_field const &
sge::systems::input::input_helpers() const
{
	return input_helpers_;
}

sge::systems::cursor_option_field const &
sge::systems::input::cursor_options() const
{
	return cursor_options_;
}
