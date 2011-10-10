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


#include <sge/input/keyboard/key_code_to_string.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/string.hpp>

fcppt::string const
sge::input::keyboard::key_code_to_string(
	keyboard::key_code::type const _code
)
{
#define MAKE_CASE(\
	name\
)\
case sge::input::keyboard::key_code::name:\
	return FCPPT_TEXT(#name);

	switch(
		_code
	)
	{
	MAKE_CASE(escape)
	MAKE_CASE(return_)
	MAKE_CASE(lshift)
	MAKE_CASE(rshift)
	MAKE_CASE(tab)
	MAKE_CASE(backspace)
	MAKE_CASE(lctrl)
	MAKE_CASE(rctrl)
	MAKE_CASE(alt)
	MAKE_CASE(altgr)
	MAKE_CASE(space)
	MAKE_CASE(insert)
	MAKE_CASE(home)
	MAKE_CASE(pageup)
	MAKE_CASE(delete_)
	MAKE_CASE(end)
	MAKE_CASE(pagedown)
	MAKE_CASE(left)
	MAKE_CASE(right)
	MAKE_CASE(up)
	MAKE_CASE(down)
	MAKE_CASE(a)
	MAKE_CASE(b)
	MAKE_CASE(c)
	MAKE_CASE(d)
	MAKE_CASE(e)
	MAKE_CASE(f)
	MAKE_CASE(g)
	MAKE_CASE(h)
	MAKE_CASE(i)
	MAKE_CASE(j)
	MAKE_CASE(k)
	MAKE_CASE(l)
	MAKE_CASE(m)
	MAKE_CASE(n)
	MAKE_CASE(o)
	MAKE_CASE(p)
	MAKE_CASE(q)
	MAKE_CASE(r)
	MAKE_CASE(s)
	MAKE_CASE(t)
	MAKE_CASE(u)
	MAKE_CASE(v)
	MAKE_CASE(w)
	MAKE_CASE(x)
	MAKE_CASE(y)
	MAKE_CASE(z)
	MAKE_CASE(_0)
	MAKE_CASE(_1)
	MAKE_CASE(_2)
	MAKE_CASE(_3)
	MAKE_CASE(_4)
	MAKE_CASE(_5)
	MAKE_CASE(_6)
	MAKE_CASE(_7)
	MAKE_CASE(_8)
	MAKE_CASE(_9)
	MAKE_CASE(f1)
	MAKE_CASE(f2)
	MAKE_CASE(f3)
	MAKE_CASE(f4)
	MAKE_CASE(f5)
	MAKE_CASE(f6)
	MAKE_CASE(f7)
	MAKE_CASE(f8)
	MAKE_CASE(f9)
	MAKE_CASE(f10)
	MAKE_CASE(f11)
	MAKE_CASE(f12)
	MAKE_CASE(f13)
	MAKE_CASE(f14)
	MAKE_CASE(f15)
	MAKE_CASE(comma)
	MAKE_CASE(colon)
	MAKE_CASE(apostrophe)
	MAKE_CASE(backslash)
	MAKE_CASE(grave)
	MAKE_CASE(substract)
	MAKE_CASE(lbracket)
	MAKE_CASE(rbracket)
	MAKE_CASE(semicolon)
	MAKE_CASE(slash)
	MAKE_CASE(underline)
	MAKE_CASE(print)
	MAKE_CASE(scroll)
	MAKE_CASE(pause)
	MAKE_CASE(lwin)
	MAKE_CASE(rwin)
	MAKE_CASE(num0)
	MAKE_CASE(num1)
	MAKE_CASE(num2)
	MAKE_CASE(num3)
	MAKE_CASE(num4)
	MAKE_CASE(num5)
	MAKE_CASE(num6)
	MAKE_CASE(num7)
	MAKE_CASE(num8)
	MAKE_CASE(num9)
	MAKE_CASE(numcomma)
	MAKE_CASE(numenter)
	MAKE_CASE(numlock)
	MAKE_CASE(add)
	MAKE_CASE(minus)
	MAKE_CASE(multiply)
	MAKE_CASE(divide)
	MAKE_CASE(equals)
	MAKE_CASE(kana)
	MAKE_CASE(kanji)
	MAKE_CASE(next)
	MAKE_CASE(numequals)
	MAKE_CASE(period)
	MAKE_CASE(yen)
	MAKE_CASE(unknown)
	}

	FCPPT_ASSERT_UNREACHABLE
}
