/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/camera/tracking/keyframe.hpp>

sge::camera::tracking::keyframe::keyframe(
	sge::camera::update_duration const &_duration,
	sge::camera::coordinate_system::object const &_coordinate_system)
:
	duration_(
		_duration),
	coordinate_system_(
		_coordinate_system)
{
}

sge::camera::update_duration const &
sge::camera::tracking::keyframe::duration() const
{
	return
		duration_;
}

sge::camera::coordinate_system::object const &
sge::camera::tracking::keyframe::coordinate_system() const
{
	return
		coordinate_system_;
}
