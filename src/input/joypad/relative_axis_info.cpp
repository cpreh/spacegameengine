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


#include <sge/input/info/optional_string.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>


sge::input::joypad::relative_axis_info::relative_axis_info(
	joypad::axis_code::type const _code,
	input::info::optional_string const &_name
)
:
	code_(
		_code
	),
	name_(
		_name
	)
{
}

sge::input::joypad::axis_code::type
sge::input::joypad::relative_axis_info::code() const
{
	return code_;
}

sge::input::info::optional_string const &
sge::input::joypad::relative_axis_info::name() const
{
	return name_;
}
