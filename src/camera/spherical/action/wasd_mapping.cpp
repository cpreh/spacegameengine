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
#include <sge/camera/spherical/action/wasd_mapping.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/optional_key_code.hpp>


sge::camera::spherical::action::mapping const
sge::camera::spherical::action::wasd_mapping()
{
	return
		spherical::action::mapping(
			spherical::action::increase_azimuth(
				sge::input::keyboard::optional_key_code(
					input::keyboard::key_code::d)),
			spherical::action::decrease_azimuth(
				sge::input::keyboard::optional_key_code(
					input::keyboard::key_code::a)),
			spherical::action::increase_inclination(
				sge::input::keyboard::optional_key_code(
					input::keyboard::key_code::w)),
			spherical::action::decrease_inclination(
				sge::input::keyboard::optional_key_code(
					input::keyboard::key_code::s)),
			spherical::action::increase_radius(
				sge::input::keyboard::optional_key_code(
					input::keyboard::key_code::left_control)),
			spherical::action::decrease_radius(
				sge::input::keyboard::optional_key_code(
					input::keyboard::key_code::space)));
}
