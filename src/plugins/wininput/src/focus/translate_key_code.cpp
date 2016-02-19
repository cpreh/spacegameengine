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


#include <sge/input/key/code.hpp>
#include <sge/wininput/focus/translate_key_code.hpp>
#include <awl/backends/windows/event/wparam.hpp>


sge::input::key::code
sge::wininput::focus::translate_key_code(
	awl::backends::windows::event::wparam const _code
)
{
	// FIXME: Add A-Z and 0-9
	switch(
		_code.get()
	)
	{
	//case VK_LBUTTON:
	//case VK_RBUTTON:
	//case VK_CANCEL:
	//case VK_MBUTTON:
	//case VK_XBUTTON1:
	//case VK_XBUTTON2:
	case VK_BACK:
		return
			sge::input::key::code::backspace;
	case VK_TAB:
		return
			sge::input::key::code::tab;
	//case VK_CLEAR:
	case VK_RETURN:
		return
			sge::input::key::code::return_;
	//case VK_SHIFT:
	//case VK_CONTROL:
	//case VK_MENU:
	case VK_PAUSE:
		return
			sge::input::key::code::pause;
	case VK_CAPITAL:
		return
			sge::input::key::code::capital;
	case VK_KANA:
		return
			sge::input::key::code::kana;
	//case VK_HANGEUL:
	//case VK_HANGUL:
	//case VK_JUNJA:
	//case VK_FINAL:
	//case VK_HANJA:
	case VK_KANJI:
		return
			sge::input::key::code::kanji;
	case VK_ESCAPE:
		return
			sge::input::key::code::escape;
	case VK_CONVERT:
		return
			sge::input::key::code::convert;
	case VK_NONCONVERT:
		return
			sge::input::key::code::noconvert;
	//case VK_ACCEPT:
	//case VK_MODECHANGE:
	case VK_SPACE:
		return
			sge::input::key::code::space;
	case VK_PRIOR:
		return
			sge::input::key::code::pageup;
	case VK_NEXT:
		return
			sge::input::key::code::pagedown;
	case VK_END:
		return
			sge::input::key::code::end;
	case VK_HOME:
		return
			sge::input::key::code::home;
	case VK_LEFT:
		return
			sge::input::key::code::left;
	case VK_UP:
		return
			sge::input::key::code::up;
	case VK_RIGHT:
		return
			sge::input::key::code::right;
	case VK_DOWN:
		return
			sge::input::key::code::down;
	//case VK_SELECT:
	case VK_PRINT:
		return
			sge::input::key::code::sysrq;
	//case VK_EXECUTE:
	//case VK_SNAPSHOT:
	case VK_INSERT:
		return
			sge::input::key::code::insert;
	case VK_DELETE:
		return
			sge::input::key::code::delete_;
//	case VK_HELP:
	case VK_LWIN:
		return
			sge::input::key::code::left_win;
	case VK_RWIN:
		return
			sge::input::key::code::right_win;
	case VK_APPS:
		return
			sge::input::key::code::apps;
	case VK_SLEEP:
		return
			sge::input::key::code::sleep;
	case VK_NUMPAD0:
		return
			sge::input::key::code::num_0;
	case VK_NUMPAD1:
		return
			sge::input::key::code::num_1;
	case VK_NUMPAD2:
		return
			sge::input::key::code::num_2;
	case VK_NUMPAD3:
		return
			sge::input::key::code::num_3;
	case VK_NUMPAD4:
		return
			sge::input::key::code::num_4;
	case VK_NUMPAD5:
		return
			sge::input::key::code::num_5;
	case VK_NUMPAD6:
		return
			sge::input::key::code::num_6;
	case VK_NUMPAD7:
		return
			sge::input::key::code::num_7;
	case VK_NUMPAD8:
		return
			sge::input::key::code::num_8;
	case VK_NUMPAD9:
		return
			sge::input::key::code::num_9;
	case VK_MULTIPLY:
		return
			sge::input::key::code::multiply;
	case VK_ADD:
		return
			sge::input::key::code::add;
	//case VK_SEPARATOR:
	case VK_SUBTRACT:
		return
			sge::input::key::code::subtract;
	case VK_DECIMAL:
		return
			sge::input::key::code::decimal;
	case VK_DIVIDE:
		return
			sge::input::key::code::divide;
	case VK_F1:
		return
			sge::input::key::code::f1;
	case VK_F2:
		return
			sge::input::key::code::f2;
	case VK_F3:
		return
			sge::input::key::code::f3;
	case VK_F4:
		return
			sge::input::key::code::f4;
	case VK_F5:
		return
			sge::input::key::code::f5;
	case VK_F6:
		return
			sge::input::key::code::f6;
	case VK_F7:
		return
			sge::input::key::code::f7;
	case VK_F8:
		return
			sge::input::key::code::f8;
	case VK_F9:
		return
			sge::input::key::code::f9;
	case VK_F10:
		return
			sge::input::key::code::f10;
	case VK_F11:
		return
			sge::input::key::code::f11;
	case VK_F12:
		return
			sge::input::key::code::f12;
	case VK_F13:
		return
			sge::input::key::code::f13;
	case VK_F14:
		return
			sge::input::key::code::f14;
	case VK_F15:
		return
			sge::input::key::code::f15;
	//case VK_F16:
	//case VK_F17:
	//case VK_F18:
	//case VK_F19:
	//case VK_F20:
	//case VK_F21:
	//case VK_F22:
	//case VK_F23:
	//case VK_F24:
	case VK_NUMLOCK:
		return
			sge::input::key::code::num_lock;
	case VK_SCROLL:
		return
			sge::input::key::code::scroll;
	//case VK_OEM_NEC_EQUAL:
	//case VK_OEM_FJ_JISHO:
	//case VK_OEM_FJ_MASSHOU:
	//case VK_OEM_FJ_TOUROKU:
	//case VK_OEM_FJ_LOYA:
	//case VK_OEM_FJ_ROYA:
	case VK_LSHIFT:
		return
			sge::input::key::code::left_shift;
	case VK_RSHIFT:
		return
			sge::input::key::code::right_shift;
	case VK_LCONTROL:
		return
			sge::input::key::code::left_control;
	case VK_RCONTROL:
		return
			sge::input::key::code::right_control;
	case VK_LMENU:
		return
			sge::input::key::code::left_alt;
	case VK_RMENU:
		return
			sge::input::key::code::right_alt;
	//case VK_BROWSER_BACK:
	//case VK_BROWSER_FORWARD:
	//case VK_BROWSER_REFRESH:
	//case VK_BROWSER_STOP:
	//case VK_BROWSER_SEARCH:
	//case VK_BROWSER_FAVORITES:
	//case VK_BROWSER_HOME:

	//case VK_VOLUME_MUTE:
	//case VK_VOLUME_DOWN:
	//case VK_VOLUME_UP:
	//case VK_MEDIA_NEXT_TRACK:
	//case VK_MEDIA_PREV_TRACK:
	//case VK_MEDIA_STOP:
	//case VK_MEDIA_PLAY_PAUSE:
	//case VK_LAUNCH_MAIL:
	//case VK_LAUNCH_MEDIA_SELECT:
	//case VK_LAUNCH_APP1:
	//case VK_LAUNCH_APP2:
	//case VK_OEM_1:
	//case VK_OEM_PLUS:
	//case VK_OEM_COMMA:
	//case VK_OEM_MINUS:
	//case VK_OEM_PERIOD:
	//case VK_OEM_2:
	//case VK_OEM_3:
	//case VK_OEM_4:
	//case VK_OEM_5:
	//case VK_OEM_6:
	//case VK_OEM_7:
	//case VK_OEM_8:

	//case VK_OEM_AX:
	//case VK_OEM_102:
	//case VK_ICO_HELP:
	//case VK_ICO_00:
	//case VK_PROCESSKEY:
	//case VK_ICO_CLEAR:

	//case VK_PACKET:

	//case VK_OEM_RESET:
	//case VK_OEM_JUMP:
	//case VK_OEM_PA1:
	//case VK_OEM_PA2:
	//case VK_OEM_PA3:
	//case VK_OEM_WSCTRL:
	//case VK_OEM_CUSEL:
	//case VK_OEM_ATTN:
	//case VK_OEM_FINISH:
	//case VK_OEM_COPY:
	//case VK_OEM_AUTO:
	//case VK_OEM_ENLW:
	//case VK_OEM_BACKTAB:

	//case VK_ATTN:
	//case VK_CRSEL:
	//case VK_EXSEL:
	//case VK_EREOF:
	//case VK_PLAY:
	//case VK_ZOOM:
	//case VK_NONAME:
	//case VK_PA1:
	//case VK_OEM_CLEAR:
	}

	return
		sge::input::key::code::unknown;
}
