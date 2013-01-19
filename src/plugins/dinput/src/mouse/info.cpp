/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/dinput/mouse/axis_map.hpp>
#include <sge/dinput/mouse/button_map.hpp>
#include <sge/dinput/mouse/info.hpp>
#include <sge/input/mouse/info.hpp>


sge::dinput::mouse::info::info(
	sge::input::mouse::info const &_input_info,
	sge::dinput::mouse::axis_map const &_axis_map,
	sge::dinput::mouse::button_map const &_button_map
)
:
	input_info_(
		_input_info
	),
	axis_map_(
		_axis_map
	),
	button_map_(
		_button_map
	)
{
}

sge::input::mouse::info const &
sge::dinput::mouse::info::input_info() const
{
	return
		input_info_;
}

sge::dinput::mouse::axis_map const &
sge::dinput::mouse::info::axis_map() const
{
	return
		axis_map_;
}

sge::dinput::mouse::button_map const &
sge::dinput::mouse::info::button_map() const
{
	return
		button_map_;
}
