/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_INPUT_KEYBOARD_KEY_CODE_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_KEY_CODE_HPP_INCLUDED


namespace sge
{
namespace input
{
namespace keyboard
{

namespace key_code
{
enum type
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
	print = sysrq,
	unlabeled,
	yen,
	unknown
};
}

}
}
}

#endif
