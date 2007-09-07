/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

sge::dinput::key_converter::key_converter()
: v(256,kc::none)
{
	v[DIK_0] = kc::key_0;
	v[DIK_1] = kc::key_1;
	v[DIK_2] = kc::key_2;
	v[DIK_3] = kc::key_3;
	v[DIK_4] = kc::key_4;
	v[DIK_5] = kc::key_5;
	v[DIK_6] = kc::key_6;
	v[DIK_7] = kc::key_7;
	v[DIK_8] = kc::key_8;
	v[DIK_9] = kc::key_9;
	v[DIK_A] = kc::key_a;
//	v[DIK_ABNT_C1] = kc::key_ABNT_C1;
//	v[DIK_ABNT_C2] = kc::key_ABNT_C2;
	v[DIK_ADD] = kc::key_add;
	v[DIK_APOSTROPHE] = kc::key_apostrophe;
//	v[DIK_APPS] = kc::key_apps;
//	v[DIK_AT] = kc::key_at;
//	v[DIK_AX] = kc::key_AX;
	v[DIK_B] = kc::key_b;
	v[DIK_BACK] = kc::key_backspace;
//	v[DIK_BACKSLASH] = kc::key_backslash;
	v[DIK_C] = kc::key_c;
//	v[DIK_CALCULATOR] = kc::key_CALC;
//	v[DIK_CAPITAL] = kc::key_capital;
	v[DIK_COLON] = kc::key_colon;
	v[DIK_COMMA] = kc::key_comma;
//	v[DIK_CONVERT] = kc::key_dEFAULT;
	v[DIK_D] = kc::key_d;
//	v[DIK_DECIMAL] = kc::key_decimal;
	v[DIK_DELETE] = kc::key_delete;
	v[DIK_DIVIDE] = kc::key_divide;
	v[DIK_DOWN] = kc::key_down;
	v[DIK_E] = kc::key_e;
	v[DIK_END] = kc::key_end;
	v[DIK_EQUALS] = kc::key_equals;
	v[DIK_ESCAPE] = kc::key_escape;
	v[DIK_F] = kc::key_f;
	v[DIK_F1] = kc::key_f1;
	v[DIK_F2] = kc::key_f2;
	v[DIK_F3] = kc::key_f3;
	v[DIK_F4] = kc::key_f4;
	v[DIK_F5] = kc::key_f5;
	v[DIK_F6] = kc::key_f6;
	v[DIK_F7] = kc::key_f7;
	v[DIK_F8] = kc::key_f8;
	v[DIK_F9] = kc::key_f9;
	v[DIK_F10] = kc::key_f10;
	v[DIK_F11] = kc::key_f11;
	v[DIK_F12] = kc::key_f12;
	v[DIK_F13] = kc::key_f13;
	v[DIK_F14] = kc::key_f14;
	v[DIK_F15] = kc::key_f15;
	v[DIK_G] = kc::key_g;
//	v[DIK_GRAVE] = kc::key_grave;
	v[DIK_H] = kc::key_h;
	v[DIK_HOME] = kc::key_home;
	v[DIK_I] = kc::key_i;
	v[DIK_INSERT] = kc::key_insert;
	v[DIK_J] = kc::key_j;
	v[DIK_K] = kc::key_k;
	v[DIK_KANA] = kc::key_kana;
	v[DIK_KANJI] = kc::key_kanji;
	v[DIK_L] = kc::key_l;
	v[DIK_LBRACKET] = kc::key_lbracket;
	v[DIK_LCONTROL] = kc::key_lctrl;
	v[DIK_LEFT] = kc::key_left;
	v[DIK_LMENU] = kc::key_alt;
	v[DIK_LSHIFT] = kc::key_lshift;
	v[DIK_LWIN] = kc::key_lwin;
	v[DIK_M] = kc::key_m;
//	v[DIK_MAIL] = kc::key_MAIL;
	v[DIK_MINUS] = kc::key_minus;
	v[DIK_MULTIPLY] = kc::key_multiply;
	v[DIK_N] = kc::key_n;
	v[DIK_NEXT] = kc::key_next;
//	v[DIK_NOCONVERT] = kc::key_noconvert;
	v[DIK_NUMLOCK] = kc::key_numlock;
	v[DIK_NUMPAD0] = kc::key_num0;
	v[DIK_NUMPAD1] = kc::key_num1;
	v[DIK_NUMPAD2] = kc::key_num2;
	v[DIK_NUMPAD3] = kc::key_num3;
	v[DIK_NUMPAD4] = kc::key_num4;
	v[DIK_NUMPAD5] = kc::key_num5;
	v[DIK_NUMPAD6] = kc::key_num6;
	v[DIK_NUMPAD7] = kc::key_num7;
	v[DIK_NUMPAD8] = kc::key_num8;
	v[DIK_NUMPAD9] = kc::key_num9;
	v[DIK_NUMPADEQUALS] = kc::key_numequals;
	v[DIK_O] = kc::key_o;
	v[DIK_P] = kc::key_p;
	v[DIK_PAUSE] = kc::key_pause;
	v[DIK_PERIOD] = kc::key_period;
//	v[DIK_POWER] = kc::key_power;
//	v[DIK_PRIOR] = kc::key_prior;
	v[DIK_Q] = kc::key_q;
	v[DIK_R] = kc::key_r;
	v[DIK_RBRACKET] =  kc::key_rbracket;
	v[DIK_RCONTROL] = kc::key_rctrl;
	v[DIK_RETURN] = kc::key_return;
	v[DIK_RIGHT] = kc::key_right;
	v[DIK_RMENU] = kc::key_altgr;
	v[DIK_RSHIFT] = kc::key_rshift;
	v[DIK_RWIN] = kc::key_rwin;
	v[DIK_S] = kc::key_s;
	v[DIK_SCROLL] = kc::key_scroll;
	v[DIK_SEMICOLON] = kc::key_semicolon;
	v[DIK_SLASH] = kc::key_slash;
//	v[DIK_SLEEP] = kc::key_sleep;
	v[DIK_SPACE] = kc::key_space;
//	v[DIK_STOP] = kc::key_stop;
	v[DIK_SUBTRACT] = kc::key_substract;
//	v[DIK_SYSRQ] = kc::key_sysrq;
	v[DIK_T] = kc::key_t;
	v[DIK_TAB] = kc::key_tab;
	v[DIK_U] = kc::key_u;
	v[DIK_UNDERLINE] = kc::key_underline;
//	v[DIK_UNLABELED] = kc::key_unlabeled;
	v[DIK_UP] = kc::key_up;
	v[DIK_V] = kc::key_v;
	v[DIK_W] = kc::key_w;
	v[DIK_X] = kc::key_x;
	v[DIK_Y] = kc::key_y;
	v[DIK_YEN] = kc::key_yen;
	v[DIK_Z] = kc::key_z;

	for(key_vector::size_type i = 0; i < v.size(); ++i)
		vr[v[i]] = static_cast<DWORD>(i);
}

sge::key_code sge::dinput::key_converter::create_key_code(const DWORD ofs) const
{
	return v.at(ofs);
}

DWORD sge::dinput::key_converter::create_dik(const key_code key) const
{
	return vr.find(key)->second;
}
