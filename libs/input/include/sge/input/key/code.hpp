//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_KEY_CODE_HPP_INCLUDED
#define SGE_INPUT_KEY_CODE_HPP_INCLUDED

#include <sge/input/key/code_fwd.hpp>


namespace sge
{
namespace input
{
namespace key
{

// TODO: Split this into focus/keyboard
// Focus should only use semantic keys, e.g. insert.
// Keyboard should distinguish individual keys, e.g. insert, num_insert.
enum class code
{
	escape,
	return_,
	left_shift,
	right_shift,
	tab,
	backspace,
	left_control,
	right_control,
	left_alt,
	right_alt,
	space,
	capital,
	insert,
	home,
	pageup,
	delete_,
	end,
	pagedown,
	left,
	right,
	up,
	down,
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	f1,
	f2,
	f3,
	f4,
	f5,
	f6,
	f7,
	f8,
	f9,
	f10,
	f11,
	f12,
	f13,
	f14,
	f15,
	comma,
	colon,
	decimal,
	apostrophe,
	backslash,
	grave,
	subtract,
	left_bracket,
	right_bracket,
	semicolon,
	slash,
	underline,
	scroll,
	pause,
	left_win,
	right_win,
	num_0,
	num_1,
	num_2,
	num_3,
	num_4,
	num_5,
	num_6,
	num_7,
	num_8,
	num_9,
	num_comma,
	num_enter,
	num_equals,
	num_lock,
	add,
	minus,
	multiply,
	divide,
	apps,
	circumflex,
	at,
	ax,
	equals,
	kana,
	kanji,
	convert,
	noconvert,
	period,
	power,
	sleep,
	stop,
	sysrq,
	unlabeled,
	yen,
	unknown
};

}
}
}

#endif
