/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/camera/coordinate_system/object.hpp>

sge::camera::coordinate_system::object::object(
	coordinate_system::right const &_right,
	coordinate_system::up const &_up,
	coordinate_system::forward const &_forward,
	coordinate_system::position const &_position)
:
	right_(
		_right),
	up_(
		_up),
	forward_(
		_forward),
	position_(
		_position)
{
}

sge::camera::coordinate_system::right const &
sge::camera::coordinate_system::object::right() const
{
	return
		right_;
}

void
sge::camera::coordinate_system::object::right(
	coordinate_system::right const &_right)
{
	right_ =
		_right;
}

sge::camera::coordinate_system::up const &
sge::camera::coordinate_system::object::up() const
{
	return
		up_;
}

void
sge::camera::coordinate_system::object::up(
	coordinate_system::up const &_up)
{
	up_ =
		_up;
}

sge::camera::coordinate_system::forward const &
sge::camera::coordinate_system::object::forward() const
{
	return
		forward_;
}

void
sge::camera::coordinate_system::object::forward(
	coordinate_system::forward const &_forward)
{
	forward_ =
		_forward;
}

sge::camera::coordinate_system::position const &
sge::camera::coordinate_system::object::position() const
{
	return position_;
}

void
sge::camera::coordinate_system::object::position(
	coordinate_system::position const &_position)
{
	position_ =
		_position;
}
