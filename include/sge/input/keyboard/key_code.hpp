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
	lshift,
	rshift,
	tab,
	backspace,
	lctrl,
	rctrl,
	alt,
	altgr,
	space,
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
//	DECIMAL,
	apostrophe,
	backslash,
	grave,
	substract,
	lbracket,
	rbracket,
	semicolon,
	slash,
	underline,
	print,
	scroll,
	pause,
	lwin,
	rwin,
	num0,
	num1,
	num2,
	num3,
	num4,
	num5,
	num6,
	num7,
	num8,
	num9,
	numcomma,
	numenter,
	numlock,
	add,
	minus,
	multiply,
	divide,
//	apps,
//	at,
//	ax,
	equals,
	kana,
	kanji,
	next,
//	noconvert,
	numequals,
	period,
//	power,
//	prior,
//	sleep,
//	stop,
//	sysrq,
//	unlabeled,
	yen,
	unknown
};
}

}
}
}

#endif
