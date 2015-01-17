/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/camera/ortho_freelook/action/mapping.hpp>
#include <sge/camera/ortho_freelook/action/wsg_mapping.hpp>
#include <sge/input/keyboard/optional_key_code.hpp>


sge::camera::ortho_freelook::action::mapping const
sge::camera::ortho_freelook::action::wsg_mapping()
{
	return
		sge::camera::ortho_freelook::action::mapping(
			sge::camera::ortho_freelook::action::zoom_in(
				sge::input::keyboard::optional_key_code(
					sge::input::keyboard::key_code::w)),
			sge::camera::ortho_freelook::action::zoom_out(
				sge::input::keyboard::optional_key_code(
					sge::input::keyboard::key_code::s)),
			sge::camera::ortho_freelook::action::activate_pan(
				sge::input::keyboard::optional_key_code(
					sge::input::keyboard::key_code::g)));
}
