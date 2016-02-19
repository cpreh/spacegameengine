/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/input/key/code.hpp>


sge::input::key::code
sge::dinput::keyboard::translate_key_code(
	DWORD const _ofs
)
{
	switch(
		_ofs
	)
	{
	case DIK_0:
		return sge::input::key::code::_0;
	case DIK_1:
		return sge::input::key::code::_1;
	case DIK_2:
		return sge::input::key::code::_2;
	case DIK_3:
		return sge::input::key::code::_3;
	case DIK_4:
		return sge::input::key::code::_4;
	case DIK_5:
		return sge::input::key::code::_5;
	case DIK_6:
		return sge::input::key::code::_6;
	case DIK_7:
		return sge::input::key::code::_7;
	case DIK_8:
		return sge::input::key::code::_8;
	case DIK_9:
		return sge::input::key::code::_9;
	case DIK_A:
		return sge::input::key::code::a;
//	case DIK_ABNT_C1:
//		return sge::input::key::code::key_ABNT_C1;
//	case DIK_ABNT_C2:
//		return sge::input::key::code::key_ABNT_C2;
	case DIK_ADD:
		return sge::input::key::code::add;
	case DIK_APOSTROPHE:
		return sge::input::key::code::apostrophe;
	case DIK_APPS:
		return sge::input::key::code::apps;
	case DIK_AT:
		return sge::input::key::code::at;
	case DIK_AX:
		return sge::input::key::code::ax;
	case DIK_B:
		return sge::input::key::code::b;
	case DIK_BACK:
		return sge::input::key::code::backspace;
	case DIK_BACKSLASH:
		return sge::input::key::code::backslash;
	case DIK_C:
		return sge::input::key::code::c;
//	case DIK_CALCULATOR:
//		return sge::input::key::code::key_CALC;
	case DIK_CAPITAL:
		return sge::input::key::code::capital;
	case DIK_COLON:
		return sge::input::key::code::colon;
	case DIK_COMMA:
		return sge::input::key::code::comma;
	case DIK_CONVERT:
		return sge::input::key::code::convert;
	case DIK_D:
		return sge::input::key::code::d;
	case DIK_DECIMAL:
		return sge::input::key::code::decimal;
	case DIK_DELETE:
		return sge::input::key::code::delete_;
	case DIK_DIVIDE:
		return sge::input::key::code::divide;
	case DIK_DOWN:
		return sge::input::key::code::down;
	case DIK_E:
		return sge::input::key::code::e;
	case DIK_END:
		return sge::input::key::code::end;
	case DIK_EQUALS:
		return sge::input::key::code::equals;
	case DIK_ESCAPE:
		return sge::input::key::code::escape;
	case DIK_F:
		return sge::input::key::code::f;
	case DIK_F1:
		return sge::input::key::code::f1;
	case DIK_F2:
		return sge::input::key::code::f2;
	case DIK_F3:
		return sge::input::key::code::f3;
	case DIK_F4:
		return sge::input::key::code::f4;
	case DIK_F5:
		return sge::input::key::code::f5;
	case DIK_F6:
		return sge::input::key::code::f6;
	case DIK_F7:
		return sge::input::key::code::f7;
	case DIK_F8:
		return sge::input::key::code::f8;
	case DIK_F9:
		return sge::input::key::code::f9;
	case DIK_F10:
		return sge::input::key::code::f10;
	case DIK_F11:
		return sge::input::key::code::f11;
	case DIK_F12:
		return sge::input::key::code::f12;
	case DIK_F13:
		return sge::input::key::code::f13;
	case DIK_F14:
		return sge::input::key::code::f14;
	case DIK_F15:
		return sge::input::key::code::f15;
	case DIK_G:
		return sge::input::key::code::g;
	case DIK_GRAVE:
		return sge::input::key::code::grave;
	case DIK_H:
		return sge::input::key::code::h;
	case DIK_HOME:
		return sge::input::key::code::home;
	case DIK_I:
		return sge::input::key::code::i;
	case DIK_INSERT:
		return sge::input::key::code::insert;
	case DIK_J:
		return sge::input::key::code::j;
	case DIK_K:
		return sge::input::key::code::k;
	case DIK_KANA:
		return sge::input::key::code::kana;
	case DIK_KANJI:
		return sge::input::key::code::kanji;
	case DIK_L:
		return sge::input::key::code::l;
	case DIK_LBRACKET:
		return sge::input::key::code::left_bracket;
	case DIK_LCONTROL:
		return sge::input::key::code::left_control;
	case DIK_LEFT:
		return sge::input::key::code::left;
	case DIK_LMENU:
		return sge::input::key::code::left_alt;
	case DIK_LSHIFT:
		return sge::input::key::code::left_shift;
	case DIK_LWIN:
		return sge::input::key::code::left_win;
	case DIK_M:
		return sge::input::key::code::m;
//	case DIK_MAIL:
//		return sge::input::key::code::key_MAIL;
	case DIK_MINUS:
		return sge::input::key::code::minus;
	case DIK_MULTIPLY:
		return sge::input::key::code::multiply;
	case DIK_N:
		return sge::input::key::code::n;
//	case DIK_NEXT:
//		return sge::input::key::code::next;
	case DIK_NOCONVERT:
		return sge::input::key::code::noconvert;
	case DIK_NUMLOCK:
		return sge::input::key::code::num_lock;
	case DIK_NUMPAD0:
		return sge::input::key::code::num_0;
	case DIK_NUMPAD1:
		return sge::input::key::code::num_1;
	case DIK_NUMPAD2:
		return sge::input::key::code::num_2;
	case DIK_NUMPAD3:
		return sge::input::key::code::num_3;
	case DIK_NUMPAD4:
		return sge::input::key::code::num_4;
	case DIK_NUMPAD5:
		return sge::input::key::code::num_5;
	case DIK_NUMPAD6:
		return sge::input::key::code::num_6;
	case DIK_NUMPAD7:
		return sge::input::key::code::num_7;
	case DIK_NUMPAD8:
		return sge::input::key::code::num_8;
	case DIK_NUMPAD9:
		return sge::input::key::code::num_9;
	case DIK_NUMPADEQUALS:
		return sge::input::key::code::num_equals;
	case DIK_O:
		return sge::input::key::code::o;
	case DIK_P:
		return sge::input::key::code::p;
	case DIK_PAUSE:
		return sge::input::key::code::pause;
	case DIK_PERIOD:
		return sge::input::key::code::period;
	case DIK_POWER:
		return sge::input::key::code::power;
//	case DIK_PRIOR:
//		return sge::input::key::code::key_prior;
	case DIK_Q:
		return sge::input::key::code::q;
	case DIK_R:
		return sge::input::key::code::r;
	case DIK_RBRACKET:
		return sge:: input::key::code::right_bracket;
	case DIK_RCONTROL:
		return sge::input::key::code::right_control;
	case DIK_RETURN:
		return sge::input::key::code::return_;
	case DIK_RIGHT:
		return sge::input::key::code::right;
	case DIK_RMENU:
		return sge::input::key::code::right_alt;
	case DIK_RSHIFT:
		return sge::input::key::code::right_shift;
	case DIK_RWIN:
		return sge::input::key::code::right_win;
	case DIK_S:
		return sge::input::key::code::s;
	case DIK_SCROLL:
		return sge::input::key::code::scroll;
	case DIK_SEMICOLON:
		return sge::input::key::code::semicolon;
	case DIK_SLASH:
		return sge::input::key::code::slash;
	case DIK_SLEEP:
		return sge::input::key::code::sleep;
	case DIK_SPACE:
		return sge::input::key::code::space;
	case DIK_STOP:
		return sge::input::key::code::stop;
	case DIK_SUBTRACT:
		return sge::input::key::code::subtract;
	case DIK_SYSRQ:
		return sge::input::key::code::sysrq;
	case DIK_T:
		return sge::input::key::code::t;
	case DIK_TAB:
		return sge::input::key::code::tab;
	case DIK_U:
		return sge::input::key::code::u;
	case DIK_UNDERLINE:
		return sge::input::key::code::underline;
	case DIK_UNLABELED:
		return sge::input::key::code::unlabeled;
	case DIK_UP:
		return sge::input::key::code::up;
	case DIK_V:
		return sge::input::key::code::v;
	case DIK_W:
		return sge::input::key::code::w;
	case DIK_X:
		return sge::input::key::code::x;
	case DIK_Y:
		return sge::input::key::code::y;
	case DIK_YEN:
		return sge::input::key::code::yen;
	case DIK_Z:
		return sge::input::key::code::z;
	}

	return sge::input::key::code::unknown;
}
