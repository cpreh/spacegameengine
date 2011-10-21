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


#include <sge/input/mouse/info.hpp>
#include <fcppt/string.hpp>


sge::input::mouse::info::info(
	input::mouse::axis_info_container const &_axis,
	input::mouse::button_info_container const &_buttons,
	input::info::name const &_name
)
:
	axis_(
		_axis
	),
	buttons_(
		_buttons
	),
	name_(
		_name
	)
{
}

sge::input::mouse::axis_info_container const &
sge::input::mouse::info::axis() const
{
	return axis_;
}

sge::input::mouse::button_info_container const &
sge::input::mouse::info::buttons() const
{
	return buttons_;
}

sge::input::info::name const &
sge::input::mouse::info::name() const
{
	return name_;
}
