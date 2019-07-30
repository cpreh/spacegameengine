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


#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/sdlinput/cursor/object.hpp>


sge::sdlinput::cursor::object::object(
	sge::window::object &_window
)
:
	sge::input::cursor::object{},
	window_{
		_window
	}
{
}

sge::sdlinput::cursor::object::~object()
{
}

sge::window::object &
sge::sdlinput::cursor::object::window() const
{
	return
		this->window_;
}

sge::input::cursor::optional_position
sge::sdlinput::cursor::object::position() const
{
	// TODO
	return
		sge::input::cursor::optional_position{};
}

void
sge::sdlinput::cursor::object::mode(
	sge::input::cursor::mode const _mode
)
{
}
