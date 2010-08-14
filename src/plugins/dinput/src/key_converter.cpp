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


#include "../key_converter.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

sge::dinput::key_converter::key_converter()
:
	v(
		256,
		input::kc::none)
{
	v[DIK_0] = input::kc::key_0;
	v[DIK_1] = input::kc::key_1;
	v[DIK_2] = input::kc::key_2;
	v[DIK_3] = input::kc::key_3;
	v[DIK_4] = input::kc::key_4;
	v[DIK_5] = input::kc::key_5;
	v[DIK_6] = input::kc::key_6;
	v[DIK_7] = input::kc::key_7;
	v[DIK_8] = input::kc::key_8;
	v[DIK_9] = input::kc::key_9;
	v[DIK_A] = input::kc::key_a;
//	v[DIK_ABNT_C1] = input::kc::key_ABNT_C1;
//	v[DIK_ABNT_C2] = input::kc::key_ABNT_C2;
	v[DIK_ADD] = input::kc::key_add;
	v[DIK_APOSTROPHE] = input::kc::key_apostrophe;
//	v[DIK_APPS] = input::kc::key_apps;
//	v[DIK_AT] = input::kc::key_at;
//	v[DIK_AX] = input::kc::key_AX;
	v[DIK_B] = input::kc::key_b;
	v[DIK_BACK] = input::kc::key_backspace;
//	v[DIK_BACKSLASH] = input::kc::key_backslash;
	v[DIK_C] = input::kc::key_c;
//	v[DIK_CALCULATOR] = input::kc::key_CALC;
//	v[DIK_CAPITAL] = input::kc::key_capital;
	v[DIK_COLON] = input::kc::key_colon;
	v[DIK_COMMA] = input::kc::key_comma;
//	v[DIK_CONVERT] = input::kc::key_dEFAULT;
	v[DIK_D] = input::kc::key_d;
//	v[DIK_DECIMAL] = input::kc::key_decimal;
	v[DIK_DELETE] = input::kc::key_delete;
	v[DIK_DIVIDE] = input::kc::key_divide;
	v[DIK_DOWN] = input::kc::key_down;
	v[DIK_E] = input::kc::key_e;
	v[DIK_END] = input::kc::key_end;
	v[DIK_EQUALS] = input::kc::key_equals;
	v[DIK_ESCAPE] = input::kc::key_escape;
	v[DIK_F] = input::kc::key_f;
	v[DIK_F1] = input::kc::key_f1;
	v[DIK_F2] = input::kc::key_f2;
	v[DIK_F3] = input::kc::key_f3;
	v[DIK_F4] = input::kc::key_f4;
	v[DIK_F5] = input::kc::key_f5;
	v[DIK_F6] = input::kc::key_f6;
	v[DIK_F7] = input::kc::key_f7;
	v[DIK_F8] = input::kc::key_f8;
	v[DIK_F9] = input::kc::key_f9;
	v[DIK_F10] = input::kc::key_f10;
	v[DIK_F11] = input::kc::key_f11;
	v[DIK_F12] = input::kc::key_f12;
	v[DIK_F13] = input::kc::key_f13;
	v[DIK_F14] = input::kc::key_f14;
	v[DIK_F15] = input::kc::key_f15;
	v[DIK_G] = input::kc::key_g;
//	v[DIK_GRAVE] = input::kc::key_grave;
	v[DIK_H] = input::kc::key_h;
	v[DIK_HOME] = input::kc::key_home;
	v[DIK_I] = input::kc::key_i;
	v[DIK_INSERT] = input::kc::key_insert;
	v[DIK_J] = input::kc::key_j;
	v[DIK_K] = input::kc::key_k;
	v[DIK_KANA] = input::kc::key_kana;
	v[DIK_KANJI] = input::kc::key_kanji;
	v[DIK_L] = input::kc::key_l;
	v[DIK_LBRACKET] = input::kc::key_lbracket;
	v[DIK_LCONTROL] = input::kc::key_lctrl;
	v[DIK_LEFT] = input::kc::key_left;
	v[DIK_LMENU] = input::kc::key_alt;
	v[DIK_LSHIFT] = input::kc::key_lshift;
	v[DIK_LWIN] = input::kc::key_lwin;
	v[DIK_M] = input::kc::key_m;
//	v[DIK_MAIL] = input::kc::key_MAIL;
	v[DIK_MINUS] = input::kc::key_minus;
	v[DIK_MULTIPLY] = input::kc::key_multiply;
	v[DIK_N] = input::kc::key_n;
	v[DIK_NEXT] = input::kc::key_next;
//	v[DIK_NOCONVERT] = input::kc::key_noconvert;
	v[DIK_NUMLOCK] = input::kc::key_numlock;
	v[DIK_NUMPAD0] = input::kc::key_num0;
	v[DIK_NUMPAD1] = input::kc::key_num1;
	v[DIK_NUMPAD2] = input::kc::key_num2;
	v[DIK_NUMPAD3] = input::kc::key_num3;
	v[DIK_NUMPAD4] = input::kc::key_num4;
	v[DIK_NUMPAD5] = input::kc::key_num5;
	v[DIK_NUMPAD6] = input::kc::key_num6;
	v[DIK_NUMPAD7] = input::kc::key_num7;
	v[DIK_NUMPAD8] = input::kc::key_num8;
	v[DIK_NUMPAD9] = input::kc::key_num9;
	v[DIK_NUMPADEQUALS] = input::kc::key_numequals;
	v[DIK_O] = input::kc::key_o;
	v[DIK_P] = input::kc::key_p;
	v[DIK_PAUSE] = input::kc::key_pause;
	v[DIK_PERIOD] = input::kc::key_period;
//	v[DIK_POWER] = input::kc::key_power;
//	v[DIK_PRIOR] = input::kc::key_prior;
	v[DIK_Q] = input::kc::key_q;
	v[DIK_R] = input::kc::key_r;
	v[DIK_RBRACKET] =  input::kc::key_rbracket;
	v[DIK_RCONTROL] = input::kc::key_rctrl;
	v[DIK_RETURN] = input::kc::key_return;
	v[DIK_RIGHT] = input::kc::key_right;
	v[DIK_RMENU] = input::kc::key_altgr;
	v[DIK_RSHIFT] = input::kc::key_rshift;
	v[DIK_RWIN] = input::kc::key_rwin;
	v[DIK_S] = input::kc::key_s;
	v[DIK_SCROLL] = input::kc::key_scroll;
	v[DIK_SEMICOLON] = input::kc::key_semicolon;
	v[DIK_SLASH] = input::kc::key_slash;
//	v[DIK_SLEEP] = input::kc::key_sleep;
	v[DIK_SPACE] = input::kc::key_space;
//	v[DIK_STOP] = input::kc::key_stop;
	v[DIK_SUBTRACT] = input::kc::key_substract;
//	v[DIK_SYSRQ] = input::kc::key_sysrq;
	v[DIK_T] = input::kc::key_t;
	v[DIK_TAB] = input::kc::key_tab;
	v[DIK_U] = input::kc::key_u;
	v[DIK_UNDERLINE] = input::kc::key_underline;
//	v[DIK_UNLABELED] = input::kc::key_unlabeled;
	v[DIK_UP] = input::kc::key_up;
	v[DIK_V] = input::kc::key_v;
	v[DIK_W] = input::kc::key_w;
	v[DIK_X] = input::kc::key_x;
	v[DIK_Y] = input::kc::key_y;
	v[DIK_YEN] = input::kc::key_yen;
	v[DIK_Z] = input::kc::key_z;

	for(key_vector::size_type i = 0; i < v.size(); ++i)
		vr[v[i]] = static_cast<DWORD>(i);
}

sge::input::key_code
sge::dinput::key_converter::create_key_code(
	DWORD const ofs) const
{
	return v.at(ofs);
}

DWORD
sge::dinput::key_converter::create_dik(
	input::key_code const key) const
{
	reverse_map::const_iterator const it(
		vr.find(
			key
		)
	);

	if(it == vr.end())
		throw exception(
			FCPPT_TEXT("Input key not found in reverse map!")
		);

	return it->second;
}
