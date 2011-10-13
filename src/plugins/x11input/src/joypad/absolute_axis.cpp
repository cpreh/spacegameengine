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


#include <sge/x11input/joypad/absolute_axis.hpp>
#include <sge/x11input/joypad/axis.hpp>
#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/info/id.hpp>

sge::input::joypad::absolute_axis const
sge::x11input::joypad::absolute_axis(
	input::info::id const _id,
	input::joypad::absolute_axis_info_container const &_info
)
{
	return
		joypad::axis<
			sge::input::joypad::absolute_axis
		>(
			_id,
			_info
		);
}
