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
	// FIXME
	switch(
		_code
	)
	{
	case SDLK_UNKNOWN:
	case SDLK_RETURN:
	case SDLK_ESCAPE:
		return
			sge::input::key::code::escape;
	case SDLK_BACKSPACE:
	case SDLK_TAB:
	case SDLK_SPACE:
	case SDLK_EXCLAIM:
	case SDLK_QUOTEDBL:
	case SDLK_HASH:
	case SDLK_PERCENT:
	case SDLK_DOLLAR:
	case SDLK_AMPERSAND:
	case SDLK_QUOTE:
	case SDLK_LEFTPAREN:
	case SDLK_RIGHTPAREN:
	case SDLK_ASTERISK:
	case SDLK_PLUS:
	case SDLK_COMMA:
	case SDLK_MINUS:
	case SDLK_PERIOD:
	case SDLK_SLASH:
	case SDLK_0:
	case SDLK_1:
	case SDLK_2:
	case SDLK_3:
	case SDLK_4:
	case SDLK_5:
	case SDLK_6:
	case SDLK_7:
	case SDLK_8:
	case SDLK_9:
	case SDLK_COLON:
	case SDLK_SEMICOLON:
	case SDLK_LESS:
	case SDLK_EQUALS:
	case SDLK_GREATER:
	case SDLK_QUESTION:
	case SDLK_AT:
	case SDLK_LEFTBRACKET:
	case SDLK_BACKSLASH:
	case SDLK_RIGHTBRACKET:
	case SDLK_CARET:
	case SDLK_UNDERSCORE:
	case SDLK_BACKQUOTE:
	case SDLK_a:
	case SDLK_b:
	case SDLK_c:
	case SDLK_d:
	case SDLK_e:
	case SDLK_f:
	case SDLK_g:
	case SDLK_h:
	case SDLK_i:
	case SDLK_j:
	case SDLK_k:
	case SDLK_l:
	case SDLK_m:
	case SDLK_n:
	case SDLK_o:
	case SDLK_p:
	case SDLK_q:
	case SDLK_r:
	case SDLK_s:
	case SDLK_t:
	case SDLK_u:
	case SDLK_v:
	case SDLK_w:
	case SDLK_x:
	case SDLK_y:
	case SDLK_z:

	case SDLK_CAPSLOCK:

	case SDLK_F1:
	case SDLK_F2:
	case SDLK_F3:
	case SDLK_F4:
	case SDLK_F5:
	case SDLK_F6:
	case SDLK_F7:
	case SDLK_F8:
	case SDLK_F9:
	case SDLK_F10:
	case SDLK_F11:
	case SDLK_F12:

	case SDLK_PRINTSCREEN:
	case SDLK_SCROLLLOCK:
	case SDLK_PAUSE:
	case SDLK_INSERT:
	case SDLK_HOME:
	case SDLK_PAGEUP:
	case SDLK_DELETE:
	case SDLK_END:
	case SDLK_PAGEDOWN:
	case SDLK_RIGHT:
	case SDLK_LEFT:
	case SDLK_DOWN:
	case SDLK_UP:

	case SDLK_NUMLOCKCLEAR:
	case SDLK_KP_DIVIDE:
	case SDLK_KP_MULTIPLY:
	case SDLK_KP_MINUS:
	case SDLK_KP_PLUS:
	case SDLK_KP_ENTER:
	case SDLK_KP_1:
	case SDLK_KP_2:
	case SDLK_KP_3:
	case SDLK_KP_4:
	case SDLK_KP_5:
	case SDLK_KP_6:
	case SDLK_KP_7:
	case SDLK_KP_8:
	case SDLK_KP_9:
	case SDLK_KP_0:
	case SDLK_KP_PERIOD:

	case SDLK_APPLICATION:
	case SDLK_POWER:
	case SDLK_KP_EQUALS:
	case SDLK_F13:
	case SDLK_F14:
	case SDLK_F15:
	case SDLK_F16:
	case SDLK_F17:
	case SDLK_F18:
	case SDLK_F19:
	case SDLK_F20:
	case SDLK_F21:
	case SDLK_F22:
	case SDLK_F23:
	case SDLK_F24:
	case SDLK_EXECUTE:
	case SDLK_HELP:
	case SDLK_MENU:
	case SDLK_SELECT:
	case SDLK_STOP:
	case SDLK_AGAIN:
	case SDLK_UNDO:
	case SDLK_CUT:
	case SDLK_COPY:
	case SDLK_PASTE:
	case SDLK_FIND:
	case SDLK_MUTE:
	case SDLK_VOLUMEUP:
	case SDLK_VOLUMEDOWN:
	case SDLK_KP_COMMA:
	case SDLK_KP_EQUALSAS400:
	case SDLK_ALTERASE:
	case SDLK_SYSREQ:
	case SDLK_CANCEL:
	case SDLK_CLEAR:
	case SDLK_PRIOR:
	case SDLK_RETURN2:
	case SDLK_SEPARATOR:
	case SDLK_OUT:
	case SDLK_OPER:
	case SDLK_CLEARAGAIN:
	case SDLK_CRSEL:
	case SDLK_EXSEL:

	case SDLK_KP_00:
	case SDLK_KP_000:
	case SDLK_THOUSANDSSEPARATOR:
	case SDLK_DECIMALSEPARATOR:
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

	case SDLK_LCTRL:
	case SDLK_LSHIFT:
	case SDLK_LALT:
	case SDLK_LGUI:
	case SDLK_RCTRL:
	case SDLK_RSHIFT:
	case SDLK_RALT:
	case SDLK_RGUI:

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
	case SDLK_EJECT:
	case SDLK_SLEEP:
	case SDLK_APP1:
	case SDLK_APP2:

	case SDLK_AUDIOREWIND:
	case SDLK_AUDIOFASTFORWARD:
		return
			sge::input::key::code::unknown;
	}

	return
		sge::input::key::code::unknown;
}
