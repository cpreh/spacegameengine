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


#include <sge/input/keyboard/key.hpp>

sge::input::keyboard::key::key(
	key_code::type const _code,
	keyboard::char_type const _character
)
:
	code_(_code),
	character_(_character)
{
}

sge::input::keyboard::key_code::type
sge::input::keyboard::key::code() const
{
	return code_;
}

sge::input::keyboard::char_type
sge::input::keyboard::key::character() const
{
	return character_;
}

bool
sge::input::keyboard::operator==(
	keyboard::key const &_a,
	keyboard::key const &_b
)
{
	return
		_a.code() == _b.code()
		&& _a.character() == _b.character();
}

bool
sge::input::keyboard::operator!=(
	keyboard::key const &_a,
	keyboard::key const &_b
)
{
	return
		!(_a == _b);
}
