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


#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/base.hpp>
#include <sge/input/joypad/event/relative_axis.hpp>


sge::input::joypad::event::relative_axis::relative_axis(
	sge::input::joypad::shared_ptr const _joypad,
	sge::input::joypad::relative_axis const &_axis,
	sge::input::joypad::axis_value const _axis_value
)
:
	sge::input::joypad::event::base{
		_joypad
	},
	axis_{
		_axis
	},
	axis_value_{
		_axis_value
	}
{
}

sge::input::joypad::event::relative_axis::~relative_axis()
{
}

sge::input::joypad::relative_axis const &
sge::input::joypad::event::relative_axis::axis() const
{
	return
		axis_;
}

sge::input::joypad::axis_value
sge::input::joypad::event::relative_axis::value() const
{
	return
		axis_value_;
}
