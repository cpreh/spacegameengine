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


#ifndef SGE_KEY_TYPE_HPP_INCLUDED
#define SGE_KEY_TYPE_HPP_INCLUDED

#include <utility>
#include "../string.hpp"

namespace sge
{

struct mod_state {
	mod_state(bool shift, bool ctrl, bool alt)
	 : shift(shift),
	   ctrl(ctrl),
	   alt(alt)
	{}

	bool shift,
	     ctrl,
	     alt;
};

enum key_code {
	KC_None,
	KC_DEFAULT,
	KC_ESC,
	KC_RETURN,
	KC_LSHIFT,
	KC_RSHIFT,
	KC_TAB,
	KC_BACK,
	KC_CAPITAL,
	KC_LCTRL,
	KC_RCTRL,
	KC_ALT,
	KC_ALTGR,
	KC_SPACE,
	KC_INS,
	KC_HOME,
	KC_PGUP,
	KC_DEL,
	KC_END,
	KC_PGDN,
	KC_LEFT,
	KC_RIGHT,
	KC_UP,
	KC_DOWN,
	KC_A,
	KC_B,
	KC_C,
	KC_D,
	KC_E,
	KC_F,
	KC_G,
	KC_H,
	KC_I,
	KC_J,
	KC_K,
	KC_L,
	KC_M,
	KC_N,
	KC_O,
	KC_P,
	KC_Q,
	KC_R,
	KC_S,
	KC_T,
	KC_U,
	KC_V,
	KC_W,
	KC_X,
	KC_Y,
	KC_Z,
	KC_0,
	KC_1,
	KC_2,
	KC_3,
	KC_4,
	KC_5,
	KC_6,
	KC_7,
	KC_8,
	KC_9,
	KC_F1,
	KC_F2,
	KC_F3,
	KC_F4,
	KC_F5,
	KC_F6,
	KC_F7,
	KC_F8,
	KC_F9,
	KC_F10,
	KC_F11,
	KC_F12,
	KC_F13,
	KC_F14,
	KC_F15,
	KC_COMMA,
	KC_COLON,
	KC_DECIMAL,
	KC_APOSTROPHE,
	KC_BACKSLASH,
	KC_GRAVE,
	KC_SUBSTRACT,
	KC_LBRACKET,
	KC_RBRACKET,
	KC_SEMICOLON,
	KC_SLASH,
	KC_UNDERLINE,
	KC_SCROLL,
	KC_PAUSE,
	KC_LWIN,
	KC_RWIN,
	KC_NUM0,
	KC_NUM1,
	KC_NUM2,
	KC_NUM3,
	KC_NUM4,
	KC_NUM5,
	KC_NUM6,
	KC_NUM7,
	KC_NUM8,
	KC_NUM9,
	KC_NUMCOMMA,
	KC_NUMENTER,
	KC_NUMLOCK,
	KC_ADD,
	KC_MINUS,
	KC_MULTIPLY,
	KC_DIVIDE,
	KC_APPS,
	KC_AT,
	KC_AX,
	KC_EQUALS,
	KC_KANA,
	KC_KANJI,
	KC_NEXT,
	KC_NOCONVERT,
	KC_NUMEQUALS,
	KC_PERIOD,
	KC_POWER,
	KC_PRIOR,
	KC_SLEEP,
	KC_STOP,
	KC_SYSRQ,
	KC_UNLABELED,
	KC_YEN,
	KC_MOUSEL,
	KC_MOUSER,
	KC_MOUSEX,
	KC_MOUSEXNEG,
	KC_MOUSEXPOS,
	KC_MOUSEY,
	KC_MOUSEYNEG,
	KC_MOUSEYPOS,
	KC_MOUSEZ,
	KC_MOUSEZNEG,
	KC_MOUSEZPOS,
	KC_num_keys
};

struct key_type {
	typedef uchar_t char_type;
	key_type(const string& name = string(), const key_code code = KC_None, const char_type char_code = 0)
		: name(name), code(code), char_code(char_code) {}
	string name;
	key_code code;
	char_type char_code;
};
	
inline bool operator<(const key_type& l, const key_type& r)
{
	return l.name < r.name;
}
	
inline bool operator==(const key_type& l, const key_type& r)
{
	return l.name == r.name && l.char_code == r.char_code;
}
	
inline bool operator!=(const key_type& l, const key_type& r)
{
	return !(l==r);
}

inline bool is_mouse_key(const key_code key)
{
	switch(key) {
	case KC_MOUSEL:
	case KC_MOUSER:
		return true;
	default:
		return false;
	}
}
	
inline bool is_mouse_axis(const key_code key)
{
	switch(key) {
	case KC_MOUSEX:
	case KC_MOUSEY:
	case KC_MOUSEXNEG:
	case KC_MOUSEXPOS:
	case KC_MOUSEYNEG:
	case KC_MOUSEYPOS:
		return true;
	default:
		return false;
	}
}
	
inline bool is_keyboard_key(const key_code key)
{
	return !(is_mouse_key(key) || is_mouse_axis(key));
}

inline bool is_shift(const key_code key)
{
	switch(key) {
	case KC_LSHIFT:
	case KC_RSHIFT:
	      return true;
	default:
	      return false;
	}
}

inline bool is_ctrl(const key_code key)
{
	switch(key) {
	case KC_LCTRL:
	case KC_RCTRL:
	case KC_ALTGR:
		return true;
	default:
		return false;
	}
}

inline bool is_alt(const key_code key)
{
	switch(key) {
	case KC_ALT:
	case KC_ALTGR:
		return true;
	default:
		return false;
	}
}

typedef float key_state;
typedef std::pair<key_type,key_state> key_pair;

}

#endif
