//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/key/code.hpp>
#include <sge/input/key/code_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string
sge::input::key::code_to_string(
	sge::input::key::code const _code
)
{
#define MAKE_CASE(\
	name\
)\
case sge::input::key::code::name:\
	return \
		FCPPT_TEXT(\
			#name\
		);

	switch(
		_code
	)
	{
	MAKE_CASE(escape)
	MAKE_CASE(return_)
	MAKE_CASE(left_shift)
	MAKE_CASE(right_shift)
	MAKE_CASE(tab)
	MAKE_CASE(backspace)
	MAKE_CASE(left_control)
	MAKE_CASE(right_control)
	MAKE_CASE(left_alt)
	MAKE_CASE(right_alt)
	MAKE_CASE(space)
	MAKE_CASE(capital)
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
	MAKE_CASE(decimal)
	MAKE_CASE(apostrophe)
	MAKE_CASE(backslash)
	MAKE_CASE(grave)
	MAKE_CASE(subtract)
	MAKE_CASE(left_bracket)
	MAKE_CASE(right_bracket)
	MAKE_CASE(semicolon)
	MAKE_CASE(slash)
	MAKE_CASE(underline)
	MAKE_CASE(scroll)
	MAKE_CASE(pause)
	MAKE_CASE(left_win)
	MAKE_CASE(right_win)
	MAKE_CASE(num_0)
	MAKE_CASE(num_1)
	MAKE_CASE(num_2)
	MAKE_CASE(num_3)
	MAKE_CASE(num_4)
	MAKE_CASE(num_5)
	MAKE_CASE(num_6)
	MAKE_CASE(num_7)
	MAKE_CASE(num_8)
	MAKE_CASE(num_9)
	MAKE_CASE(num_comma)
	MAKE_CASE(num_enter)
	MAKE_CASE(num_equals)
	MAKE_CASE(num_lock)
	MAKE_CASE(add)
	MAKE_CASE(minus)
	MAKE_CASE(multiply)
	MAKE_CASE(divide)
	MAKE_CASE(apps)
	MAKE_CASE(circumflex)
	MAKE_CASE(at)
	MAKE_CASE(ax)
	MAKE_CASE(equals)
	MAKE_CASE(kana)
	MAKE_CASE(kanji)
	MAKE_CASE(convert)
	MAKE_CASE(noconvert)
	MAKE_CASE(period)
	MAKE_CASE(power)
	MAKE_CASE(sleep)
	MAKE_CASE(stop)
	MAKE_CASE(sysrq)
	MAKE_CASE(unlabeled)
	MAKE_CASE(yen)
	MAKE_CASE(unknown)
	}

	FCPPT_ASSERT_UNREACHABLE;
}
