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


#include <sge/camera/spherical/coordinate_system/look_down_positive_z.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <fcppt/math/pi.hpp>

sge::camera::spherical::coordinate_system::object const
sge::camera::spherical::coordinate_system::look_down_positive_z(
	spherical::coordinate_system::radius const &_radius)
{
	return
		spherical::coordinate_system::object(
			spherical::coordinate_system::azimuth(
				-fcppt::math::pi<sge::renderer::scalar>()/2.0f),
			spherical::coordinate_system::inclination(
				-fcppt::math::pi<sge::renderer::scalar>()/2.0f),
			_radius);
}
