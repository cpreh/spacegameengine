#ifndef SGE_KEY_TYPE_HPP_INCLUDED
#define SGE_KEY_TYPE_HPP_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include "../main/types.hpp"

namespace sge
{
	struct modifier_state {
		modifier_state(bool shift_down = false, bool ctrl_down = false, bool alt_down = false)
			: shift_down(shift_down), ctrl_down(ctrl_down), alt_down(alt_down) {}
			bool shift_down;
			bool ctrl_down;
			bool alt_down;
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
		KC_ABNT_C1,
		KC_ABNT_C2,
		KC_APPS,
		KC_AT,
		KC_AX,
		KC_CALC,
		KC_EQUALS,
		KC_KANA,
		KC_KANJI,
		KC_MAIL,
		KC_MEDIASELECT,
		KC_MEDIASTOP,
		KC_MUTE,
		KC_MYCOMPUTER,
		KC_NEXT,
		KC_NEXTTRACK,
		KC_NOCONVERT,
		KC_NUMEQUALS,
		KC_OEM_102,
		KC_PERIOD,
		KC_PLAYPAUSE,
		KC_POWER,
		KC_PREVTRACK,
		KC_PRIOR,
		KC_SLEEP,
		KC_STOP,
		KC_SYSRQ,
		KC_UNLABELED,
		KC_VOLUMEDOWN,
		KC_VOLUMEUP,
		KC_WAKE,
		KC_WEBBACK,
		KC_WEBFAVORTIES,
		KC_WEBFORWARD,
		KC_WEBHOME,
		KC_WEBREFRESH,
		KC_WEBSEARCH,
		KC_WEBSTOP,
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
		typedef char char_type;
		key_type(const std::string& name, const modifier_state& state = modifier_state(), const key_code code = KC_None, const char_type char_code = 0)
			: name(name), state(state), code(code), char_code(char_code) {}
		std::string name;
		modifier_state state;
		key_code code;
		char_type char_code;
	};
	
	inline bool operator<(const key_type& l, const key_type& r)
	{
		return l.name < r.name;
	}
	
	inline bool operator==(const key_type& l, const key_type& r)
	{
		return l.name == r.name;
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

	typedef float key_state;
	typedef std::pair<key_type,key_state> key_pair;

	typedef std::vector<key_pair> input_array;
}

#endif
