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


#include <sge/input/key/pressed.hpp>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/keyboard/event/base.hpp>
#include <sge/input/keyboard/event/key.hpp>


sge::input::keyboard::event::key::key(
	sge::input::keyboard::shared_ptr const _keyboard,
	sge::input::keyboard::key const &_key,
	sge::input::key::pressed const _pressed
)
:
	sge::input::keyboard::event::base{
		_keyboard
	},
	key_{
		_key
	},
	pressed_{
		_pressed
	}
{
}

sge::input::keyboard::event::key::~key()
{
}

sge::input::keyboard::key const &
sge::input::keyboard::event::key::get() const
{
	return
		key_;
}

bool
sge::input::keyboard::event::key::pressed() const
{
	return
		pressed_.get();
}
