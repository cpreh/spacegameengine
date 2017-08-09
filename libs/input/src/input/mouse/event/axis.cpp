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


#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_value.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/input/mouse/event/base.hpp>


sge::input::mouse::event::axis::axis(
	sge::input::mouse::shared_ptr const _mouse,
	sge::input::mouse::axis const &_axis,
	sge::input::mouse::axis_value const _value
)
:
	sge::input::mouse::event::base{
		_mouse
	},
	axis_{
		_axis
	},
	value_{
		_value
	}
{
}

sge::input::mouse::event::axis::~axis()
{
}

sge::input::mouse::axis const &
sge::input::mouse::event::axis::get() const
{
	return
		axis_;
}

sge::input::mouse::axis_code
sge::input::mouse::event::axis::code() const
{
	return
		axis_.code();
}

sge::input::mouse::axis_value
sge::input::mouse::event::axis::value() const
{
	return
		value_;
}
