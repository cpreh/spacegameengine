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


#include <sge/camera/first_person/action/mapping.hpp>

sge::camera::first_person::action::mapping::mapping(
	action::left const &_left,
	action::right const &_right,
	action::up const &_up,
	action::down const &_down,
	action::forward const &_forward,
	action::backward const &_backward)
:
	left_(
		_left),
	right_(
		_right),
	up_(
		_up),
	down_(
		_down),
	forward_(
		_forward),
	backward_(
		_backward)
{
}

sge::camera::first_person::action::left const &
sge::camera::first_person::action::mapping::left() const
{
	return
		left_;
}

sge::camera::first_person::action::right const &
sge::camera::first_person::action::mapping::right() const
{
	return
		right_;
}

sge::camera::first_person::action::up const &
sge::camera::first_person::action::mapping::up() const
{
	return
		up_;
}

sge::camera::first_person::action::down const &
sge::camera::first_person::action::mapping::down() const
{
	return
		down_;
}

sge::camera::first_person::action::forward const &
sge::camera::first_person::action::mapping::forward() const
{
	return
		forward_;
}

sge::camera::first_person::action::backward const &
sge::camera::first_person::action::mapping::backward() const
{
	return
		backward_;
}
