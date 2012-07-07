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


#include <sge/dinput/di.hpp>
#include <sge/dinput/keyboard/translate_key_code.hpp>
#include <sge/input/keyboard/key_code.hpp>


sge::input::keyboard::key_code::type
sge::dinput::keyboard::translate_key_code(
	DWORD const _ofs
)
{
	switch(
		_ofs
	)
	{
	case DIK_0:
		return sge::input::keyboard::key_code::_0;
	case DIK_1:
		return sge::input::keyboard::key_code::_1;
	case DIK_2:
		return sge::input::keyboard::key_code::_2;
	case DIK_3:
		return sge::input::keyboard::key_code::_3;
	case DIK_4:
		return sge::input::keyboard::key_code::_4;
	case DIK_5:
		return sge::input::keyboard::key_code::_5;
	case DIK_6:
		return sge::input::keyboard::key_code::_6;
	case DIK_7:
		return sge::input::keyboard::key_code::_7;
	case DIK_8:
		return sge::input::keyboard::key_code::_8;
	case DIK_9:
		return sge::input::keyboard::key_code::_9;
	case DIK_A:
		return sge::input::keyboard::key_code::a;
//	case DIK_ABNT_C1:
//		return sge::input::keyboard::key_code::key_ABNT_C1;
//	case DIK_ABNT_C2:
//		return sge::input::keyboard::key_code::key_ABNT_C2;
	case DIK_ADD:
		return sge::input::keyboard::key_code::add;
	case DIK_APOSTROPHE:
		return sge::input::keyboard::key_code::apostrophe;
	case DIK_APPS:
		return sge::input::keyboard::key_code::apps;
	case DIK_AT:
		return sge::input::keyboard::key_code::at;
	case DIK_AX:
		return sge::input::keyboard::key_code::ax;
	case DIK_B:
		return sge::input::keyboard::key_code::b;
	case DIK_BACK:
		return sge::input::keyboard::key_code::backspace;
	case DIK_BACKSLASH:
		return sge::input::keyboard::key_code::backslash;
	case DIK_C:
		return sge::input::keyboard::key_code::c;
//	case DIK_CALCULATOR:
//		return sge::input::keyboard::key_code::key_CALC;
	case DIK_CAPITAL:
		return sge::input::keyboard::key_code::capital;
	case DIK_COLON:
		return sge::input::keyboard::key_code::colon;
	case DIK_COMMA:
		return sge::input::keyboard::key_code::comma;
	case DIK_CONVERT:
		return sge::input::keyboard::key_code::convert;
	case DIK_D:
		return sge::input::keyboard::key_code::d;
	case DIK_DECIMAL:
		return sge::input::keyboard::key_code::decimal;
	case DIK_DELETE:
		return sge::input::keyboard::key_code::delete_;
	case DIK_DIVIDE:
		return sge::input::keyboard::key_code::divide;
	case DIK_DOWN:
		return sge::input::keyboard::key_code::down;
	case DIK_E:
		return sge::input::keyboard::key_code::e;
	case DIK_END:
		return sge::input::keyboard::key_code::end;
	case DIK_EQUALS:
		return sge::input::keyboard::key_code::equals;
	case DIK_ESCAPE:
		return sge::input::keyboard::key_code::escape;
	case DIK_F:
		return sge::input::keyboard::key_code::f;
	case DIK_F1:
		return sge::input::keyboard::key_code::f1;
	case DIK_F2:
		return sge::input::keyboard::key_code::f2;
	case DIK_F3:
		return sge::input::keyboard::key_code::f3;
	case DIK_F4:
		return sge::input::keyboard::key_code::f4;
	case DIK_F5:
		return sge::input::keyboard::key_code::f5;
	case DIK_F6:
		return sge::input::keyboard::key_code::f6;
	case DIK_F7:
		return sge::input::keyboard::key_code::f7;
	case DIK_F8:
		return sge::input::keyboard::key_code::f8;
	case DIK_F9:
		return sge::input::keyboard::key_code::f9;
	case DIK_F10:
		return sge::input::keyboard::key_code::f10;
	case DIK_F11:
		return sge::input::keyboard::key_code::f11;
	case DIK_F12:
		return sge::input::keyboard::key_code::f12;
	case DIK_F13:
		return sge::input::keyboard::key_code::f13;
	case DIK_F14:
		return sge::input::keyboard::key_code::f14;
	case DIK_F15:
		return sge::input::keyboard::key_code::f15;
	case DIK_G:
		return sge::input::keyboard::key_code::g;
	case DIK_GRAVE:
		return sge::input::keyboard::key_code::grave;
	case DIK_H:
		return sge::input::keyboard::key_code::h;
	case DIK_HOME:
		return sge::input::keyboard::key_code::home;
	case DIK_I:
		return sge::input::keyboard::key_code::i;
	case DIK_INSERT:
		return sge::input::keyboard::key_code::insert;
	case DIK_J:
		return sge::input::keyboard::key_code::j;
	case DIK_K:
		return sge::input::keyboard::key_code::k;
	case DIK_KANA:
		return sge::input::keyboard::key_code::kana;
	case DIK_KANJI:
		return sge::input::keyboard::key_code::kanji;
	case DIK_L:
		return sge::input::keyboard::key_code::l;
	case DIK_LBRACKET:
		return sge::input::keyboard::key_code::left_bracket;
	case DIK_LCONTROL:
		return sge::input::keyboard::key_code::left_control;
	case DIK_LEFT:
		return sge::input::keyboard::key_code::left;
	case DIK_LMENU:
		return sge::input::keyboard::key_code::left_alt;
	case DIK_LSHIFT:
		return sge::input::keyboard::key_code::left_shift;
	case DIK_LWIN:
		return sge::input::keyboard::key_code::left_win;
	case DIK_M:
		return sge::input::keyboard::key_code::m;
//	case DIK_MAIL:
//		return sge::input::keyboard::key_code::key_MAIL;
	case DIK_MINUS:
		return sge::input::keyboard::key_code::minus;
	case DIK_MULTIPLY:
		return sge::input::keyboard::key_code::multiply;
	case DIK_N:
		return sge::input::keyboard::key_code::n;
//	case DIK_NEXT:
//		return sge::input::keyboard::key_code::next;
	case DIK_NOCONVERT:
		return sge::input::keyboard::key_code::noconvert;
	case DIK_NUMLOCK:
		return sge::input::keyboard::key_code::num_lock;
	case DIK_NUMPAD0:
		return sge::input::keyboard::key_code::num_0;
	case DIK_NUMPAD1:
		return sge::input::keyboard::key_code::num_1;
	case DIK_NUMPAD2:
		return sge::input::keyboard::key_code::num_2;
	case DIK_NUMPAD3:
		return sge::input::keyboard::key_code::num_3;
	case DIK_NUMPAD4:
		return sge::input::keyboard::key_code::num_4;
	case DIK_NUMPAD5:
		return sge::input::keyboard::key_code::num_5;
	case DIK_NUMPAD6:
		return sge::input::keyboard::key_code::num_6;
	case DIK_NUMPAD7:
		return sge::input::keyboard::key_code::num_7;
	case DIK_NUMPAD8:
		return sge::input::keyboard::key_code::num_8;
	case DIK_NUMPAD9:
		return sge::input::keyboard::key_code::num_9;
	case DIK_NUMPADEQUALS:
		return sge::input::keyboard::key_code::num_equals;
	case DIK_O:
		return sge::input::keyboard::key_code::o;
	case DIK_P:
		return sge::input::keyboard::key_code::p;
	case DIK_PAUSE:
		return sge::input::keyboard::key_code::pause;
	case DIK_PERIOD:
		return sge::input::keyboard::key_code::period;
	case DIK_POWER:
		return sge::input::keyboard::key_code::power;
//	case DIK_PRIOR:
//		return sge::input::keyboard::key_code::key_prior;
	case DIK_Q:
		return sge::input::keyboard::key_code::q;
	case DIK_R:
		return sge::input::keyboard::key_code::r;
	case DIK_RBRACKET:
		return sge:: input::keyboard::key_code::right_bracket;
	case DIK_RCONTROL:
		return sge::input::keyboard::key_code::right_control;
	case DIK_RETURN:
		return sge::input::keyboard::key_code::return_;
	case DIK_RIGHT:
		return sge::input::keyboard::key_code::right;
	case DIK_RMENU:
		return sge::input::keyboard::key_code::right_alt;
	case DIK_RSHIFT:
		return sge::input::keyboard::key_code::right_shift;
	case DIK_RWIN:
		return sge::input::keyboard::key_code::right_win;
	case DIK_S:
		return sge::input::keyboard::key_code::s;
	case DIK_SCROLL:
		return sge::input::keyboard::key_code::scroll;
	case DIK_SEMICOLON:
		return sge::input::keyboard::key_code::semicolon;
	case DIK_SLASH:
		return sge::input::keyboard::key_code::slash;
	case DIK_SLEEP:
		return sge::input::keyboard::key_code::sleep;
	case DIK_SPACE:
		return sge::input::keyboard::key_code::space;
	case DIK_STOP:
		return sge::input::keyboard::key_code::stop;
	case DIK_SUBTRACT:
		return sge::input::keyboard::key_code::subtract;
	case DIK_SYSRQ:
		return sge::input::keyboard::key_code::sysrq;
	case DIK_T:
		return sge::input::keyboard::key_code::t;
	case DIK_TAB:
		return sge::input::keyboard::key_code::tab;
	case DIK_U:
		return sge::input::keyboard::key_code::u;
	case DIK_UNDERLINE:
		return sge::input::keyboard::key_code::underline;
	case DIK_UNLABELED:
		return sge::input::keyboard::key_code::unlabeled;
	case DIK_UP:
		return sge::input::keyboard::key_code::up;
	case DIK_V:
		return sge::input::keyboard::key_code::v;
	case DIK_W:
		return sge::input::keyboard::key_code::w;
	case DIK_X:
		return sge::input::keyboard::key_code::x;
	case DIK_Y:
		return sge::input::keyboard::key_code::y;
	case DIK_YEN:
		return sge::input::keyboard::key_code::yen;
	case DIK_Z:
		return sge::input::keyboard::key_code::z;
	}

	return sge::input::keyboard::key_code::unknown;
}
