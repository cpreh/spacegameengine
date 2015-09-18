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


#include <sge/input/focus/key.hpp>
#include <sge/input/key/code.hpp>


sge::input::focus::key::key(
	sge::input::key::code const _code
)
:
	code_(
		_code
	)
{
}

sge::input::key::code
sge::input::focus::key::code() const
{
	return
		code_;
}

bool
sge::input::focus::operator==(
	sge::input::focus::key const &_left,
	sge::input::focus::key const &_right
)
{
	return
		_left.code()
		==
		_right.code();
}

bool
sge::input::focus::operator!=(
	sge::input::focus::key const &_left,
	sge::input::focus::key const &_right
)
{
	return
		!(
			_left
			==
			_right
		);
}
