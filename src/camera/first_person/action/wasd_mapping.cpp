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
#include <sge/camera/first_person/action/wasd_mapping.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/optional_key_code.hpp>


sge::camera::first_person::action::mapping const
sge::camera::first_person::action::wasd_mapping()
{
	return
		sge::camera::first_person::action::mapping(
			sge::camera::first_person::action::left(
				sge::input::keyboard::optional_key_code(
					sge::input::keyboard::key_code::a)),
			sge::camera::first_person::action::right(
				sge::input::keyboard::optional_key_code(
					sge::input::keyboard::key_code::d)),
			sge::camera::first_person::action::up(
				sge::input::keyboard::optional_key_code(
					sge::input::keyboard::key_code::space)),
			sge::camera::first_person::action::down(
				sge::input::keyboard::optional_key_code(
					sge::input::keyboard::key_code::left_control)),
			sge::camera::first_person::action::forward(
				sge::input::keyboard::optional_key_code(
					sge::input::keyboard::key_code::w)),
			sge::camera::first_person::action::backward(
				sge::input::keyboard::optional_key_code(
					sge::input::keyboard::key_code::s)));
}
