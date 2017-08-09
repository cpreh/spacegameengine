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


#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_pressed.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/base.hpp>
#include <sge/input/mouse/event/button.hpp>


sge::input::mouse::event::button::button(
	sge::input::mouse::shared_ptr const _mouse,
	sge::input::mouse::button const &_button,
	sge::input::mouse::button_pressed const _pressed
)
:
	sge::input::mouse::event::base{
		_mouse
	},
	button_{
		_button
	},
	pressed_{
		_pressed
	}
{
}

sge::input::mouse::event::button::~button()
{
}

sge::input::mouse::button_code
sge::input::mouse::event::button::button_code() const
{
	return
		button_.code();
}

sge::input::mouse::button const &
sge::input::mouse::event::button::get() const
{
	return
		button_;
}

bool
sge::input::mouse::event::button::pressed() const
{
	return
		pressed_.get();
}
