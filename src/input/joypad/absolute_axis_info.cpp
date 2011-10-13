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


#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_max.hpp>
#include <sge/input/joypad/axis_min.hpp>
#include <sge/input/info/optional_string.hpp>

sge::input::joypad::absolute_axis_info::absolute_axis_info(
	joypad::axis_code::type const _code,
	input::info::optional_string const &_name,
	joypad::axis_min const _min,
	joypad::axis_max const _max
)
:
	code_(
		_code
	),
	name_(
		_name
	),
	min_(
		_min
	),
	max_(
		_max
	)
{
}

sge::input::joypad::axis_code::type
sge::input::joypad::absolute_axis_info::code() const
{
	return code_;
}

sge::input::info::optional_string const &
sge::input::joypad::absolute_axis_info::name() const
{
	return name_;
}

sge::input::joypad::axis_min const
sge::input::joypad::absolute_axis_info::min() const
{
	return min_;
}

sge::input::joypad::axis_max const
sge::input::joypad::absolute_axis_info::max() const
{
	return max_;
}
