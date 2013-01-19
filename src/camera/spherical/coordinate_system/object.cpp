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


#include <sge/camera/spherical/coordinate_system/object.hpp>

sge::camera::spherical::coordinate_system::object::object(
	spherical::coordinate_system::azimuth const &_azimuth,
	spherical::coordinate_system::inclination const &_inclination,
	spherical::coordinate_system::radius const &_radius)
:
	azimuth_(
		_azimuth),
	inclination_(
		_inclination),
	radius_(
		_radius)
{
}

sge::camera::spherical::coordinate_system::azimuth const &
sge::camera::spherical::coordinate_system::object::azimuth() const
{
	return
		azimuth_;
}

void
sge::camera::spherical::coordinate_system::object::azimuth(
	spherical::coordinate_system::azimuth const &_azimuth)
{
	azimuth_ =
		_azimuth;
}

sge::camera::spherical::coordinate_system::inclination const &
sge::camera::spherical::coordinate_system::object::inclination() const
{
	return
		inclination_;
}

void
sge::camera::spherical::coordinate_system::object::inclination(
	spherical::coordinate_system::inclination const &_inclination)
{
	inclination_ =
		_inclination;
}

sge::camera::spherical::coordinate_system::radius const &
sge::camera::spherical::coordinate_system::object::radius() const
{
	return
		radius_;
}

void
sge::camera::spherical::coordinate_system::object::radius(
	spherical::coordinate_system::radius const &_radius)
{
	radius_ =
		_radius;
}
