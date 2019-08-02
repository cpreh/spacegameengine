//		  Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//	(See accompanying file LICENSE_1_0.txt or copy at
//		  http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/key/code.hpp>
#include <sge/sdlinput/translate/key_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_keycode.h>
#include <fcppt/config/external_end.hpp>


sge::input::key::code
sge::sdlinput::translate::key_code(
	SDL_Keycode const _code
)
{
	// TODO: We should distinguish between key codes and scan codes!
	switch(
		_code
	)
	{
	case SDLK_UNKNOWN:
		return sge::input::key::code::unknown;
	case SDLK_RETURN:
		return sge::input::key::code::return_;
	case SDLK_ESCAPE:
		return sge::input::key::code::escape;
	case SDLK_BACKSPACE:
		return sge::input::key::code::backspace;
	case SDLK_TAB:
		return sge::input::key::code::tab;
	case SDLK_SPACE:
		return sge::input::key::code::space;
	/*
	case SDLK_EXCLAIM:
	case SDLK_QUOTEDBL:
	case SDLK_HASH:
	case SDLK_PERCENT:
	case SDLK_DOLLAR:
	case SDLK_AMPERSAND:
	case SDLK_QUOTE:
	case SDLK_LEFTPAREN:
	case SDLK_RIGHTPAREN:
	case SDLK_ASTERISK:*/
	case SDLK_PLUS:
		return sge::input::key::code::add;
	case SDLK_COMMA:
		return sge::input::key::code::comma;
	case SDLK_MINUS:
		return sge::input::key::code::subtract;
	case SDLK_PERIOD:
		return sge::input::key::code::period;
	case SDLK_SLASH:
		return sge::input::key::code::slash;
	case SDLK_0:
		return sge::input::key::code::_0;
	case SDLK_1:
		return sge::input::key::code::_1;
	case SDLK_2:
		return sge::input::key::code::_2;
	case SDLK_3:
		return sge::input::key::code::_3;
	case SDLK_4:
		return sge::input::key::code::_4;
	case SDLK_5:
		return sge::input::key::code::_5;
	case SDLK_6:
		return sge::input::key::code::_6;
	case SDLK_7:
		return sge::input::key::code::_7;
	case SDLK_8:
		return sge::input::key::code::_8;
	case SDLK_9:
		return sge::input::key::code::_9;
	case SDLK_COLON:
		return sge::input::key::code::colon;
	case SDLK_SEMICOLON:
		return sge::input::key::code::semicolon;
//	case SDLK_LESS:
	case SDLK_EQUALS:
		return sge::input::key::code::equals;
//	case SDLK_GREATER:
//	case SDLK_QUESTION:
	case SDLK_AT:
		return sge::input::key::code::at;
	case SDLK_LEFTBRACKET:
		return sge::input::key::code::left_bracket;
	case SDLK_BACKSLASH:
		return sge::input::key::code::backslash;
	case SDLK_RIGHTBRACKET:
		return sge::input::key::code::right_bracket;
//	case SDLK_CARET:
	case SDLK_UNDERSCORE:
		return sge::input::key::code::underline;
//	case SDLK_BACKQUOTE:
	case SDLK_a:
		return sge::input::key::code::a;
	case SDLK_b:
		return sge::input::key::code::b;
	case SDLK_c:
		return sge::input::key::code::c;
	case SDLK_d:
		return sge::input::key::code::d;
	case SDLK_e:
		return sge::input::key::code::e;
	case SDLK_f:
		return sge::input::key::code::f;
	case SDLK_g:
		return sge::input::key::code::g;
	case SDLK_h:
		return sge::input::key::code::h;
	case SDLK_i:
		return sge::input::key::code::i;
	case SDLK_j:
		return sge::input::key::code::j;
	case SDLK_k:
		return sge::input::key::code::k;
	case SDLK_l:
		return sge::input::key::code::l;
	case SDLK_m:
		return sge::input::key::code::m;
	case SDLK_n:
		return sge::input::key::code::n;
	case SDLK_o:
		return sge::input::key::code::o;
	case SDLK_p:
		return sge::input::key::code::p;
	case SDLK_q:
		return sge::input::key::code::q;
	case SDLK_r:
		return sge::input::key::code::r;
	case SDLK_s:
		return sge::input::key::code::s;
	case SDLK_t:
		return sge::input::key::code::t;
	case SDLK_u:
		return sge::input::key::code::u;
	case SDLK_v:
		return sge::input::key::code::v;
	case SDLK_w:
		return sge::input::key::code::w;
	case SDLK_x:
		return sge::input::key::code::x;
	case SDLK_y:
		return sge::input::key::code::y;
	case SDLK_z:
		return sge::input::key::code::z;
	//case SDLK_CAPSLOCK:
	case SDLK_F1:
		return sge::input::key::code::f1;
	case SDLK_F2:
		return sge::input::key::code::f2;
	case SDLK_F3:
		return sge::input::key::code::f3;
	case SDLK_F4:
		return sge::input::key::code::f4;
	case SDLK_F5:
		return sge::input::key::code::f5;
	case SDLK_F6:
		return sge::input::key::code::f6;
	case SDLK_F7:
		return sge::input::key::code::f7;
	case SDLK_F8:
		return sge::input::key::code::f8;
	case SDLK_F9:
		return sge::input::key::code::f9;
	case SDLK_F10:
		return sge::input::key::code::f10;
	case SDLK_F11:
		return sge::input::key::code::f11;
	case SDLK_F12:
		return sge::input::key::code::f12;
//	case SDLK_PRINTSCREEN:
	case SDLK_SCROLLLOCK:
		return sge::input::key::code::scroll;
	case SDLK_PAUSE:
		return sge::input::key::code::pause;
	case SDLK_INSERT:
		return sge::input::key::code::insert;
	case SDLK_HOME:
		return sge::input::key::code::home;
	case SDLK_PAGEUP:
		return sge::input::key::code::pageup;
	case SDLK_DELETE:
		return sge::input::key::code::delete_;
	case SDLK_END:
		return sge::input::key::code::end;
	case SDLK_PAGEDOWN:
		return sge::input::key::code::pagedown;
	case SDLK_RIGHT:
		return sge::input::key::code::right;
	case SDLK_LEFT:
		return sge::input::key::code::left;
	case SDLK_DOWN:
		return sge::input::key::code::down;
	case SDLK_UP:
		return sge::input::key::code::up;
	case SDLK_NUMLOCKCLEAR:
		return sge::input::key::code::num_lock;
	case SDLK_KP_DIVIDE:
		return sge::input::key::code::divide;
	case SDLK_KP_MULTIPLY:
		return sge::input::key::code::multiply;
	case SDLK_KP_MINUS:
		return sge::input::key::code::minus;
	//case SDLK_KP_PLUS:
	case SDLK_KP_ENTER:
		return sge::input::key::code::num_enter;
	case SDLK_KP_1:
		return sge::input::key::code::num_1;
	case SDLK_KP_2:
		return sge::input::key::code::num_2;
	case SDLK_KP_3:
		return sge::input::key::code::num_3;
	case SDLK_KP_4:
		return sge::input::key::code::num_4;
	case SDLK_KP_5:
		return sge::input::key::code::num_5;
	case SDLK_KP_6:
		return sge::input::key::code::num_6;
	case SDLK_KP_7:
		return sge::input::key::code::num_7;
	case SDLK_KP_8:
		return sge::input::key::code::num_8;
	case SDLK_KP_9:
		return sge::input::key::code::num_9;
	case SDLK_KP_0:
		return sge::input::key::code::num_0;
	//case SDLK_KP_PERIOD:

	//case SDLK_APPLICATION:
	case SDLK_POWER:
		return sge::input::key::code::power;
	case SDLK_KP_EQUALS:
		return sge::input::key::code::num_equals;
	case SDLK_F13:
		return sge::input::key::code::f13;
	case SDLK_F14:
		return sge::input::key::code::f14;
	case SDLK_F15:
		return sge::input::key::code::f15;
/*
	case SDLK_F16:
	case SDLK_F17:
	case SDLK_F18:
	case SDLK_F19:
	case SDLK_F20:
	case SDLK_F21:
	case SDLK_F22:
	case SDLK_F23:
	case SDLK_F24:*/
	/*
	case SDLK_EXECUTE:
	case SDLK_HELP:
	case SDLK_MENU:
	case SDLK_SELECT:*/
	case SDLK_STOP:
		return sge::input::key::code::stop;
/*
	case SDLK_AGAIN:
	case SDLK_UNDO:
	case SDLK_CUT:
	case SDLK_COPY:
	case SDLK_PASTE:
	case SDLK_FIND:
	case SDLK_MUTE:
	case SDLK_VOLUMEUP:
	case SDLK_VOLUMEDOWN:*/
	case SDLK_KP_COMMA:
		return sge::input::key::code::num_comma;
//	case SDLK_KP_EQUALSAS400:
//	case SDLK_ALTERASE:
	case SDLK_SYSREQ:
		return sge::input::key::code::sysrq;
/*
	case SDLK_CANCEL:
	case SDLK_CLEAR:
	case SDLK_PRIOR:
	case SDLK_RETURN2:
	case SDLK_SEPARATOR:
	case SDLK_OUT:
	case SDLK_OPER:
	case SDLK_CLEARAGAIN:
	case SDLK_CRSEL:
	case SDLK_EXSEL:*/

/*
	case SDLK_KP_00:
	case SDLK_KP_000:
	case SDLK_THOUSANDSSEPARATOR:*/
	case SDLK_DECIMALSEPARATOR:
		return sge::input::key::code::decimal;
/*
	case SDLK_CURRENCYUNIT:
	case SDLK_CURRENCYSUBUNIT:
	case SDLK_KP_LEFTPAREN:
	case SDLK_KP_RIGHTPAREN:
	case SDLK_KP_LEFTBRACE:
	case SDLK_KP_RIGHTBRACE:
	case SDLK_KP_TAB:
	case SDLK_KP_BACKSPACE:
	case SDLK_KP_A:
	case SDLK_KP_B:
	case SDLK_KP_C:
	case SDLK_KP_D:
	case SDLK_KP_E:
	case SDLK_KP_F:
	case SDLK_KP_XOR:
	case SDLK_KP_POWER:
	case SDLK_KP_PERCENT:
	case SDLK_KP_LESS:
	case SDLK_KP_GREATER:
	case SDLK_KP_AMPERSAND:
	case SDLK_KP_DBLAMPERSAND:
	case SDLK_KP_VERTICALBAR:
	case SDLK_KP_DBLVERTICALBAR:
	case SDLK_KP_COLON:
	case SDLK_KP_HASH:
	case SDLK_KP_SPACE:
	case SDLK_KP_AT:
	case SDLK_KP_EXCLAM:
	case SDLK_KP_MEMSTORE:
	case SDLK_KP_MEMRECALL:
	case SDLK_KP_MEMCLEAR:
	case SDLK_KP_MEMADD:
	case SDLK_KP_MEMSUBTRACT:
	case SDLK_KP_MEMMULTIPLY:
	case SDLK_KP_MEMDIVIDE:
	case SDLK_KP_PLUSMINUS:
	case SDLK_KP_CLEAR:
	case SDLK_KP_CLEARENTRY:
	case SDLK_KP_BINARY:
	case SDLK_KP_OCTAL:
	case SDLK_KP_DECIMAL:
	case SDLK_KP_HEXADECIMAL:
	*/

	case SDLK_LCTRL:
		return sge::input::key::code::left_control;
	case SDLK_LSHIFT:
		return sge::input::key::code::left_shift;
	case SDLK_LALT:
		return sge::input::key::code::left_alt;
	// TODO
	case SDLK_LGUI:
		return sge::input::key::code::left_win;
	case SDLK_RCTRL:
		return sge::input::key::code::right_control;
	case SDLK_RSHIFT:
		return sge::input::key::code::right_shift;
	case SDLK_RALT:
		return sge::input::key::code::right_alt;
	// TODO:
	case SDLK_RGUI:
		return sge::input::key::code::right_win;

/*
	case SDLK_MODE:
	case SDLK_AUDIONEXT:
	case SDLK_AUDIOPREV:
	case SDLK_AUDIOSTOP:
	case SDLK_AUDIOPLAY:
	case SDLK_AUDIOMUTE:
	case SDLK_MEDIASELECT:
	case SDLK_WWW:
	case SDLK_MAIL:
	case SDLK_CALCULATOR:
	case SDLK_COMPUTER:
	case SDLK_AC_SEARCH:
	case SDLK_AC_HOME:
	case SDLK_AC_BACK:
	case SDLK_AC_FORWARD:
	case SDLK_AC_STOP:
	case SDLK_AC_REFRESH:
	case SDLK_AC_BOOKMARKS:

	case SDLK_BRIGHTNESSDOWN:
	case SDLK_BRIGHTNESSUP:
	case SDLK_DISPLAYSWITCH:
	case SDLK_KBDILLUMTOGGLE:
	case SDLK_KBDILLUMDOWN:
	case SDLK_KBDILLUMUP:
	case SDLK_EJECT:*/
	case SDLK_SLEEP:
		return sge::input::key::code::sleep;
	/*
	case SDLK_APP1:
	case SDLK_APP2:

	case SDLK_AUDIOREWIND:
	case SDLK_AUDIOFASTFORWARD:*/
	}

	return
		sge::input::key::code::unknown;
}
