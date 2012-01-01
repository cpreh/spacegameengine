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


#include <sge/dinput/keyboard/key_converter.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>


sge::dinput::keyboard::key_converter::key_converter()
:
	key_vector_(
		256,
		input::keyboard::key_code::unknown
	)
{
	key_vector_[DIK_0] = input::keyboard::key_code::_0;
	key_vector_[DIK_1] = input::keyboard::key_code::_1;
	key_vector_[DIK_2] = input::keyboard::key_code::_2;
	key_vector_[DIK_3] = input::keyboard::key_code::_3;
	key_vector_[DIK_4] = input::keyboard::key_code::_4;
	key_vector_[DIK_5] = input::keyboard::key_code::_5;
	key_vector_[DIK_6] = input::keyboard::key_code::_6;
	key_vector_[DIK_7] = input::keyboard::key_code::_7;
	key_vector_[DIK_8] = input::keyboard::key_code::_8;
	key_vector_[DIK_9] = input::keyboard::key_code::_9;
	key_vector_[DIK_A] = input::keyboard::key_code::a;
//	key_vector_[DIK_ABNT_C1] = input::keyboard::key_code::key_ABNT_C1;
//	key_vector_[DIK_ABNT_C2] = input::keyboard::key_code::key_ABNT_C2;
	key_vector_[DIK_ADD] = input::keyboard::key_code::add;
	key_vector_[DIK_APOSTROPHE] = input::keyboard::key_code::apostrophe;
//	key_vector_[DIK_APPS] = input::keyboard::key_code::key_apps;
//	key_vector_[DIK_AT] = input::keyboard::key_code::key_at;
//	key_vector_[DIK_AX] = input::keyboard::key_code::key_AX;
	key_vector_[DIK_B] = input::keyboard::key_code::b;
	key_vector_[DIK_BACK] = input::keyboard::key_code::backspace;
//	key_vector_[DIK_BACKSLASH] = input::keyboard::key_code::key_backslash;
	key_vector_[DIK_C] = input::keyboard::key_code::c;
//	key_vector_[DIK_CALCULATOR] = input::keyboard::key_code::key_CALC;
//	key_vector_[DIK_CAPITAL] = input::keyboard::key_code::key_capital;
	key_vector_[DIK_COLON] = input::keyboard::key_code::colon;
	key_vector_[DIK_COMMA] = input::keyboard::key_code::comma;
//	key_vector_[DIK_CONVERT] = input::keyboard::key_code::key_dEFAULT;
	key_vector_[DIK_D] = input::keyboard::key_code::d;
//	key_vector_[DIK_DECIMAL] = input::keyboard::key_code::key_decimal;
	key_vector_[DIK_DELETE] = input::keyboard::key_code::delete_;
	key_vector_[DIK_DIVIDE] = input::keyboard::key_code::divide;
	key_vector_[DIK_DOWN] = input::keyboard::key_code::down;
	key_vector_[DIK_E] = input::keyboard::key_code::e;
	key_vector_[DIK_END] = input::keyboard::key_code::end;
	key_vector_[DIK_EQUALS] = input::keyboard::key_code::equals;
	key_vector_[DIK_ESCAPE] = input::keyboard::key_code::escape;
	key_vector_[DIK_F] = input::keyboard::key_code::f;
	key_vector_[DIK_F1] = input::keyboard::key_code::f1;
	key_vector_[DIK_F2] = input::keyboard::key_code::f2;
	key_vector_[DIK_F3] = input::keyboard::key_code::f3;
	key_vector_[DIK_F4] = input::keyboard::key_code::f4;
	key_vector_[DIK_F5] = input::keyboard::key_code::f5;
	key_vector_[DIK_F6] = input::keyboard::key_code::f6;
	key_vector_[DIK_F7] = input::keyboard::key_code::f7;
	key_vector_[DIK_F8] = input::keyboard::key_code::f8;
	key_vector_[DIK_F9] = input::keyboard::key_code::f9;
	key_vector_[DIK_F10] = input::keyboard::key_code::f10;
	key_vector_[DIK_F11] = input::keyboard::key_code::f11;
	key_vector_[DIK_F12] = input::keyboard::key_code::f12;
	key_vector_[DIK_F13] = input::keyboard::key_code::f13;
	key_vector_[DIK_F14] = input::keyboard::key_code::f14;
	key_vector_[DIK_F15] = input::keyboard::key_code::f15;
	key_vector_[DIK_G] = input::keyboard::key_code::g;
//	key_vector_[DIK_GRAVE] = input::keyboard::key_code::key_grave;
	key_vector_[DIK_H] = input::keyboard::key_code::h;
	key_vector_[DIK_HOME] = input::keyboard::key_code::home;
	key_vector_[DIK_I] = input::keyboard::key_code::i;
	key_vector_[DIK_INSERT] = input::keyboard::key_code::insert;
	key_vector_[DIK_J] = input::keyboard::key_code::j;
	key_vector_[DIK_K] = input::keyboard::key_code::k;
	key_vector_[DIK_KANA] = input::keyboard::key_code::kana;
	key_vector_[DIK_KANJI] = input::keyboard::key_code::kanji;
	key_vector_[DIK_L] = input::keyboard::key_code::l;
	key_vector_[DIK_LBRACKET] = input::keyboard::key_code::lbracket;
	key_vector_[DIK_LCONTROL] = input::keyboard::key_code::lctrl;
	key_vector_[DIK_LEFT] = input::keyboard::key_code::left;
	key_vector_[DIK_LMENU] = input::keyboard::key_code::alt;
	key_vector_[DIK_LSHIFT] = input::keyboard::key_code::lshift;
	key_vector_[DIK_LWIN] = input::keyboard::key_code::lwin;
	key_vector_[DIK_M] = input::keyboard::key_code::m;
//	key_vector_[DIK_MAIL] = input::keyboard::key_code::key_MAIL;
	key_vector_[DIK_MINUS] = input::keyboard::key_code::minus;
	key_vector_[DIK_MULTIPLY] = input::keyboard::key_code::multiply;
	key_vector_[DIK_N] = input::keyboard::key_code::n;
	key_vector_[DIK_NEXT] = input::keyboard::key_code::next;
//	key_vector_[DIK_NOCONVERT] = input::keyboard::key_code::key_noconvert;
	key_vector_[DIK_NUMLOCK] = input::keyboard::key_code::numlock;
	key_vector_[DIK_NUMPAD0] = input::keyboard::key_code::num0;
	key_vector_[DIK_NUMPAD1] = input::keyboard::key_code::num1;
	key_vector_[DIK_NUMPAD2] = input::keyboard::key_code::num2;
	key_vector_[DIK_NUMPAD3] = input::keyboard::key_code::num3;
	key_vector_[DIK_NUMPAD4] = input::keyboard::key_code::num4;
	key_vector_[DIK_NUMPAD5] = input::keyboard::key_code::num5;
	key_vector_[DIK_NUMPAD6] = input::keyboard::key_code::num6;
	key_vector_[DIK_NUMPAD7] = input::keyboard::key_code::num7;
	key_vector_[DIK_NUMPAD8] = input::keyboard::key_code::num8;
	key_vector_[DIK_NUMPAD9] = input::keyboard::key_code::num9;
	key_vector_[DIK_NUMPADEQUALS] = input::keyboard::key_code::numequals;
	key_vector_[DIK_O] = input::keyboard::key_code::o;
	key_vector_[DIK_P] = input::keyboard::key_code::p;
	key_vector_[DIK_PAUSE] = input::keyboard::key_code::pause;
	key_vector_[DIK_PERIOD] = input::keyboard::key_code::period;
//	key_vector_[DIK_POWER] = input::keyboard::key_code::key_power;
//	key_vector_[DIK_PRIOR] = input::keyboard::key_code::key_prior;
	key_vector_[DIK_Q] = input::keyboard::key_code::q;
	key_vector_[DIK_R] = input::keyboard::key_code::r;
	key_vector_[DIK_RBRACKET] =  input::keyboard::key_code::rbracket;
	key_vector_[DIK_RCONTROL] = input::keyboard::key_code::rctrl;
	key_vector_[DIK_RETURN] = input::keyboard::key_code::return_;
	key_vector_[DIK_RIGHT] = input::keyboard::key_code::right;
	key_vector_[DIK_RMENU] = input::keyboard::key_code::altgr;
	key_vector_[DIK_RSHIFT] = input::keyboard::key_code::rshift;
	key_vector_[DIK_RWIN] = input::keyboard::key_code::rwin;
	key_vector_[DIK_S] = input::keyboard::key_code::s;
	key_vector_[DIK_SCROLL] = input::keyboard::key_code::scroll;
	key_vector_[DIK_SEMICOLON] = input::keyboard::key_code::semicolon;
	key_vector_[DIK_SLASH] = input::keyboard::key_code::slash;
//	key_vector_[DIK_SLEEP] = input::keyboard::key_code::key_sleep;
	key_vector_[DIK_SPACE] = input::keyboard::key_code::space;
//	key_vector_[DIK_STOP] = input::keyboard::key_code::key_stop;
	key_vector_[DIK_SUBTRACT] = input::keyboard::key_code::substract;
//	key_vector_[DIK_SYSRQ] = input::keyboard::key_code::key_sysrq;
	key_vector_[DIK_T] = input::keyboard::key_code::t;
	key_vector_[DIK_TAB] = input::keyboard::key_code::tab;
	key_vector_[DIK_U] = input::keyboard::key_code::u;
	key_vector_[DIK_UNDERLINE] = input::keyboard::key_code::underline;
//	key_vector_[DIK_UNLABELED] = input::keyboard::key_code::key_unlabeled;
	key_vector_[DIK_UP] = input::keyboard::key_code::up;
	key_vector_[DIK_V] = input::keyboard::key_code::v;
	key_vector_[DIK_W] = input::keyboard::key_code::w;
	key_vector_[DIK_X] = input::keyboard::key_code::x;
	key_vector_[DIK_Y] = input::keyboard::key_code::y;
	key_vector_[DIK_YEN] = input::keyboard::key_code::yen;
	key_vector_[DIK_Z] = input::keyboard::key_code::z;

	for(
		key_vector::size_type index = 0;
		index < key_vector_.size();
		++index
	)
		reverse_map_[
			key_vector_[
				index
			]
		] =
			static_cast<
				DWORD
			>(
				index
			);
}

sge::dinput::keyboard::key_converter::~key_converter()
{
}

sge::input::keyboard::key_code::type
sge::dinput::keyboard::key_converter::create_key_code(
	DWORD const _ofs
) const
{
	return
		key_vector_.at(
			_ofs
		);
}

DWORD
sge::dinput::keyboard::key_converter::create_dik(
	input::keyboard::key_code::type const _key
) const
{
	reverse_map::const_iterator const it(
		reverse_map_.find(
			_key
		)
	);

	if(
		it == reverse_map_.end()
	)
		throw sge::input::exception(
			FCPPT_TEXT("Input key not found in reverse map!")
		);

	return it->second;
}
