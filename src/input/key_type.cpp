/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/key_type.hpp>

sge::input::key_type::key_type(
	key_code const _code,
	char_type const _char_code
)
:
	code_(_code),
	char_code_(_char_code)
{}

sge::input::key_code
sge::input::key_type::code() const
{
	return code_;
}

sge::input::key_type::char_type
sge::input::key_type::char_code() const
{
	return char_code_;
}

void
sge::input::key_type::char_code(
	char_type const _char_code
)
{
	char_code_ = _char_code;
}

bool
sge::input::operator<(
	key_type const &l,
	key_type const &r
)
{
	return l.code() < r.code();
}

bool
sge::input::operator==(
	key_type const &l,
	key_type const &r
)
{
	return l.char_code() == r.char_code();
}

bool
sge::input::operator!=(
	key_type const &l,
	key_type const &r
)
{
	return !(l==r);
}
