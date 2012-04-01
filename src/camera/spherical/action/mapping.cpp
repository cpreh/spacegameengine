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


#include <sge/camera/spherical/action/mapping.hpp>

sge::camera::spherical::action::mapping::mapping(
	action::increase_azimuth const &_increase_azimuth,
	action::decrease_azimuth const &_decrease_azimuth,
	action::increase_inclination const &_increase_inclination,
	action::decrease_inclination const &_decrease_inclination,
	action::increase_radius const &_increase_radius,
	action::decrease_radius const &_decrease_radius)
:
	increase_azimuth_(
		_increase_azimuth),
	decrease_azimuth_(
		_decrease_azimuth),
	increase_inclination_(
		_increase_inclination),
	decrease_inclination_(
		_decrease_inclination),
	increase_radius_(
		_increase_radius),
	decrease_radius_(
		_decrease_radius)
{
}

sge::camera::spherical::action::increase_azimuth const &
sge::camera::spherical::action::mapping::increase_azimuth() const
{
	return increase_azimuth_;
}

sge::camera::spherical::action::decrease_azimuth const &
sge::camera::spherical::action::mapping::decrease_azimuth() const
{
	return decrease_azimuth_;
}

sge::camera::spherical::action::increase_inclination const &
sge::camera::spherical::action::mapping::increase_inclination() const
{
	return increase_inclination_;
}

sge::camera::spherical::action::decrease_inclination const &
sge::camera::spherical::action::mapping::decrease_inclination() const
{
	return decrease_inclination_;
}

sge::camera::spherical::action::increase_radius const &
sge::camera::spherical::action::mapping::increase_radius() const
{
	return increase_radius_;
}

sge::camera::spherical::action::decrease_radius const &
sge::camera::spherical::action::mapping::decrease_radius() const
{
	return decrease_radius_;
}
