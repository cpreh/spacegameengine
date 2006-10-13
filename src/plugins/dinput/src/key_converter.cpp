/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <algorithm>
#include "../key_converter.hpp"

sge::dinput::key_converter::key_converter()
: v(256,KC_DEFAULT)
{
	v[DIK_0] = KC_0;
	v[DIK_1] = KC_1;
	v[DIK_2] = KC_2;
	v[DIK_3] = KC_3;
	v[DIK_4] = KC_4;
	v[DIK_5] = KC_5;
	v[DIK_6] = KC_6;
	v[DIK_7] = KC_7;
	v[DIK_8] = KC_8;
	v[DIK_9] = KC_9;
	v[DIK_A] = KC_A;
	v[DIK_ABNT_C1] = KC_ABNT_C1;
	v[DIK_ABNT_C2] = KC_ABNT_C2;
	v[DIK_ADD] = KC_ADD;
	v[DIK_APOSTROPHE] = KC_APOSTROPHE;
	v[DIK_APPS] = KC_APPS;
	v[DIK_AT] = KC_AT;
	v[DIK_AX] = KC_AX;
	v[DIK_B] = KC_B;
	v[DIK_BACK] = KC_BACK;
	v[DIK_BACKSLASH] = KC_BACKSLASH;
	v[DIK_C] = KC_C;
	v[DIK_CALCULATOR] = KC_CALC;
	v[DIK_CAPITAL] = KC_CAPITAL;
	v[DIK_COLON] = KC_COLON;
	v[DIK_COMMA] = KC_COMMA;
	v[DIK_CONVERT] = KC_DEFAULT;
	v[DIK_D] = KC_D;
	v[DIK_DECIMAL] = KC_DECIMAL; 
	v[DIK_DELETE] = KC_DEL;
	v[DIK_DIVIDE] = KC_DIVIDE;
	v[DIK_DOWN] = KC_DOWN;
	v[DIK_E] = KC_E;
	v[DIK_END] = KC_END;
	v[DIK_EQUALS] = KC_EQUALS;
	v[DIK_ESCAPE] = KC_ESC;
	v[DIK_F] = KC_F;
	v[DIK_F1] = KC_F1;
	v[DIK_F2] = KC_F2;
	v[DIK_F3] = KC_F3;
	v[DIK_F4] = KC_F4;
	v[DIK_F5] = KC_F5;
	v[DIK_F6] = KC_F6;
	v[DIK_F7] = KC_F7;
	v[DIK_F8] = KC_F8;
	v[DIK_F9] = KC_F9;
	v[DIK_F10] = KC_F10;
	v[DIK_F11] = KC_F11;
	v[DIK_F12] = KC_F12;
	v[DIK_F13] = KC_F13;
	v[DIK_F14] = KC_F14;
	v[DIK_F15] = KC_F15;
	v[DIK_G] = KC_G;
	v[DIK_GRAVE] = KC_GRAVE;
	v[DIK_H] = KC_H;
	v[DIK_HOME] = KC_HOME;
	v[DIK_I] = KC_I;
	v[DIK_INSERT] = KC_INS;
	v[DIK_J] = KC_J;
	v[DIK_K] = KC_K;
	v[DIK_KANA] = KC_KANA;
	v[DIK_KANJI] = KC_KANJI;
	v[DIK_L] = KC_L;
	v[DIK_LBRACKET] = KC_LBRACKET; 
	v[DIK_LCONTROL] = KC_LCTRL;
	v[DIK_LEFT] = KC_LEFT;
	v[DIK_LMENU] = KC_ALT;
	v[DIK_LSHIFT] = KC_LSHIFT;
	v[DIK_LWIN] = KC_LWIN;
	v[DIK_M] = KC_M;
	v[DIK_MAIL] = KC_MAIL;
	v[DIK_MEDIASELECT] = KC_MEDIASELECT;
	v[DIK_MEDIASTOP] = KC_MEDIASTOP;
	v[DIK_MINUS] = KC_MINUS;
	v[DIK_MULTIPLY] = KC_MULTIPLY;
	v[DIK_MUTE] = KC_MUTE;
	v[DIK_MYCOMPUTER] = KC_MYCOMPUTER;
	v[DIK_N] = KC_N;
	v[DIK_NEXT] = KC_NEXT;
	v[DIK_NEXTTRACK] = KC_NEXTTRACK;
	v[DIK_NOCONVERT] = KC_NOCONVERT;
	v[DIK_NUMLOCK] = KC_NUMLOCK;
	v[DIK_NUMPAD0] = KC_NUM0;
	v[DIK_NUMPAD1] = KC_NUM1;
	v[DIK_NUMPAD2] = KC_NUM2;
	v[DIK_NUMPAD3] = KC_NUM3;
	v[DIK_NUMPAD4] = KC_NUM4;
	v[DIK_NUMPAD5] = KC_NUM5;
	v[DIK_NUMPAD6] = KC_NUM6;
	v[DIK_NUMPAD7] = KC_NUM7;
	v[DIK_NUMPAD8] = KC_NUM8;
	v[DIK_NUMPAD9] = KC_NUM9;
	v[DIK_NUMPADCOMMA] = KC_NUMCOMMA;
	v[DIK_NUMPADENTER] = KC_NUMENTER;
	v[DIK_NUMPADEQUALS] = KC_NUMEQUALS;
	v[DIK_O] = KC_O;
	v[DIK_OEM_102] = KC_OEM_102; 
	v[DIK_P] = KC_P;
	v[DIK_PAUSE] = KC_PAUSE;
	v[DIK_PERIOD] = KC_PERIOD;
	v[DIK_PLAYPAUSE] = KC_PLAYPAUSE;
	v[DIK_POWER] = KC_POWER;
	v[DIK_PREVTRACK] = KC_PREVTRACK;
	v[DIK_PRIOR] = KC_PRIOR;
	v[DIK_Q] = KC_Q;
	v[DIK_R] = KC_R;
	v[DIK_RBRACKET] =  KC_RBRACKET;
	v[DIK_RCONTROL] = KC_RCTRL;
	v[DIK_RETURN] = KC_RETURN;
	v[DIK_RIGHT] = KC_RIGHT;
	v[DIK_RMENU] = KC_ALTGR;
	v[DIK_RSHIFT] = KC_RSHIFT;
	v[DIK_RWIN] = KC_RWIN;
	v[DIK_S] = KC_S;
	v[DIK_SCROLL] = KC_SCROLL;
	v[DIK_SEMICOLON] = KC_SEMICOLON;
	v[DIK_SLASH] = KC_SLASH;
	v[DIK_SLEEP] = KC_SLEEP;
	v[DIK_SPACE] = KC_SPACE;
	v[DIK_STOP] = KC_STOP;
	v[DIK_SUBTRACT] = KC_SUBSTRACT;
	v[DIK_SYSRQ] = KC_SYSRQ;
	v[DIK_T] = KC_T;
	v[DIK_TAB] = KC_TAB;
	v[DIK_U] = KC_U;
	v[DIK_UNDERLINE] = KC_UNDERLINE;
	v[DIK_UNLABELED] = KC_UNLABELED;
	v[DIK_UP] = KC_UP;
	v[DIK_V] = KC_V;
	v[DIK_VOLUMEDOWN] = KC_VOLUMEDOWN;
	v[DIK_VOLUMEUP] = KC_VOLUMEUP;
	v[DIK_W] = KC_W;
	v[DIK_WAKE] = KC_WAKE;
	v[DIK_WEBBACK] = KC_WEBBACK;
	v[DIK_WEBFAVORITES] = KC_WEBFAVORTIES;
	v[DIK_WEBFORWARD] = KC_WEBFORWARD;
	v[DIK_WEBHOME] = KC_WEBHOME;
	v[DIK_WEBREFRESH] = KC_WEBREFRESH;
	v[DIK_WEBSEARCH] = KC_WEBSEARCH;
	v[DIK_WEBSTOP] = KC_WEBSTOP;
	v[DIK_X] = KC_X;
	v[DIK_Y] = KC_Y;
	v[DIK_YEN] = KC_YEN;
	v[DIK_Z] = KC_Z;

	for(unsigned i = 0; i < v.size(); ++i)
		vr[v[i]] = i;
}

sge::key_code sge::dinput::key_converter::create_key_code(const DWORD ofs) const
{
	return v.at(ofs);
}

DWORD sge::dinput::key_converter::create_dik(const key_code key) const
{
	return vr.find(key)->second;
}
