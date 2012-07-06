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


#include <sge/input/keyboard/key_code.hpp>
#include <sge/src/cegui/convert_key.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/InputEvent.h>
#include <fcppt/config/external_end.hpp>


CEGUI::Key::Scan
sge::cegui::convert_key(
	sge::input::keyboard::key_code::type const _code
)
{
	switch(
		_code
	)
	{
	case sge::input::keyboard::key_code::escape:
		return CEGUI::Key::Escape;
	case sge::input::keyboard::key_code::return_:
		return CEGUI::Key::Return;
	case sge::input::keyboard::key_code::lshift:
		return CEGUI::Key::LeftShift;
	case sge::input::keyboard::key_code::rshift:
		return CEGUI::Key::RightShift;
	case sge::input::keyboard::key_code::tab:
		return CEGUI::Key::Tab;
	case sge::input::keyboard::key_code::backspace:
		return CEGUI::Key::Backspace;
	case sge::input::keyboard::key_code::lctrl:
		return CEGUI::Key::LeftControl;
	case sge::input::keyboard::key_code::rctrl:
		return CEGUI::Key::RightControl;
	case sge::input::keyboard::key_code::alt:
		return CEGUI::Key::LeftAlt;
	case sge::input::keyboard::key_code::altgr:
		return CEGUI::Key::RightAlt;
	case sge::input::keyboard::key_code::space:
		return CEGUI::Key::Space;
	case sge::input::keyboard::key_code::insert:
		return CEGUI::Key::Insert;
	case sge::input::keyboard::key_code::home:
		return CEGUI::Key::Home;
	case sge::input::keyboard::key_code::pageup:
		return CEGUI::Key::PageUp;
	case sge::input::keyboard::key_code::delete_:
		return CEGUI::Key::Delete;
	case sge::input::keyboard::key_code::end:
		return CEGUI::Key::End;
	case sge::input::keyboard::key_code::pagedown:
		return CEGUI::Key::PageDown;
	case sge::input::keyboard::key_code::left:
		return CEGUI::Key::ArrowLeft;
	case sge::input::keyboard::key_code::right:
		return CEGUI::Key::ArrowRight;
	case sge::input::keyboard::key_code::up:
		return CEGUI::Key::ArrowUp;
	case sge::input::keyboard::key_code::down:
		return CEGUI::Key::ArrowDown;
	case sge::input::keyboard::key_code::a:
		return CEGUI::Key::A;
	case sge::input::keyboard::key_code::b:
		return CEGUI::Key::B;
	case sge::input::keyboard::key_code::c:
		return CEGUI::Key::C;
	case sge::input::keyboard::key_code::d:
		return CEGUI::Key::D;
	case sge::input::keyboard::key_code::e:
		return CEGUI::Key::E;
	case sge::input::keyboard::key_code::f:
		return CEGUI::Key::F;
	case sge::input::keyboard::key_code::g:
		return CEGUI::Key::G;
	case sge::input::keyboard::key_code::h:
		return CEGUI::Key::H;
	case sge::input::keyboard::key_code::i:
		return CEGUI::Key::I;
	case sge::input::keyboard::key_code::j:
		return CEGUI::Key::J;
	case sge::input::keyboard::key_code::k:
		return CEGUI::Key::K;
	case sge::input::keyboard::key_code::l:
		return CEGUI::Key::L;
	case sge::input::keyboard::key_code::m:
		return CEGUI::Key::M;
	case sge::input::keyboard::key_code::n:
		return CEGUI::Key::N;
	case sge::input::keyboard::key_code::o:
		return CEGUI::Key::O;
	case sge::input::keyboard::key_code::p:
		return CEGUI::Key::P;
	case sge::input::keyboard::key_code::q:
		return CEGUI::Key::Q;
	case sge::input::keyboard::key_code::r:
		return CEGUI::Key::R;
	case sge::input::keyboard::key_code::s:
		return CEGUI::Key::S;
	case sge::input::keyboard::key_code::t:
		return CEGUI::Key::T;
	case sge::input::keyboard::key_code::u:
		return CEGUI::Key::U;
	case sge::input::keyboard::key_code::v:
		return CEGUI::Key::V;
	case sge::input::keyboard::key_code::w:
		return CEGUI::Key::W;
	case sge::input::keyboard::key_code::x:
		return CEGUI::Key::X;
	case sge::input::keyboard::key_code::y:
		return CEGUI::Key::Y;
	case sge::input::keyboard::key_code::z:
		return CEGUI::Key::Z;
	case sge::input::keyboard::key_code::_0:
		return CEGUI::Key::Zero;
	case sge::input::keyboard::key_code::_1:
		return CEGUI::Key::One;
	case sge::input::keyboard::key_code::_2:
		return CEGUI::Key::Two;
	case sge::input::keyboard::key_code::_3:
		return CEGUI::Key::Three;
	case sge::input::keyboard::key_code::_4:
		return CEGUI::Key::Four;
	case sge::input::keyboard::key_code::_5:
		return CEGUI::Key::Five;
	case sge::input::keyboard::key_code::_6:
		return CEGUI::Key::Six;
	case sge::input::keyboard::key_code::_7:
		return CEGUI::Key::Seven;
	case sge::input::keyboard::key_code::_8:
		return CEGUI::Key::Eight;
	case sge::input::keyboard::key_code::_9:
		return CEGUI::Key::Nine;
	case sge::input::keyboard::key_code::f1:
		return CEGUI::Key::F1;
	case sge::input::keyboard::key_code::f2:
		return CEGUI::Key::F2;
	case sge::input::keyboard::key_code::f3:
		return CEGUI::Key::F3;
	case sge::input::keyboard::key_code::f4:
		return CEGUI::Key::F4;
	case sge::input::keyboard::key_code::f5:
		return CEGUI::Key::F5;
	case sge::input::keyboard::key_code::f6:
		return CEGUI::Key::F6;
	case sge::input::keyboard::key_code::f7:
		return CEGUI::Key::F7;
	case sge::input::keyboard::key_code::f8:
		return CEGUI::Key::F8;
	case sge::input::keyboard::key_code::f9:
		return CEGUI::Key::F9;
	case sge::input::keyboard::key_code::f10:
		return CEGUI::Key::F10;
	case sge::input::keyboard::key_code::f11:
		return CEGUI::Key::F11;
	case sge::input::keyboard::key_code::f12:
		return CEGUI::Key::F12;
	case sge::input::keyboard::key_code::f13:
		return CEGUI::Key::F13;
	case sge::input::keyboard::key_code::f14:
		return CEGUI::Key::F14;
	case sge::input::keyboard::key_code::f15:
		return CEGUI::Key::F15;
	case sge::input::keyboard::key_code::comma:
		return CEGUI::Key::Comma;
	case sge::input::keyboard::key_code::colon:
		return CEGUI::Key::Colon;
//	DECIMAL:
	case sge::input::keyboard::key_code::apostrophe:
		return CEGUI::Key::Apostrophe;
	case sge::input::keyboard::key_code::backslash:
		return CEGUI::Key::Backslash;
	case sge::input::keyboard::key_code::grave:
		return CEGUI::Key::Grave;
	case sge::input::keyboard::key_code::substract:
		return CEGUI::Key::Subtract;
	case sge::input::keyboard::key_code::lbracket:
		return CEGUI::Key::LeftBracket;
	case sge::input::keyboard::key_code::rbracket:
		return CEGUI::Key::RightBracket;
	case sge::input::keyboard::key_code::semicolon:
		return CEGUI::Key::Semicolon;
	case sge::input::keyboard::key_code::slash:
		return CEGUI::Key::Slash;
	case sge::input::keyboard::key_code::underline:
		return CEGUI::Key::Underline;
	case sge::input::keyboard::key_code::print:
		return CEGUI::Key::SysRq;
	case sge::input::keyboard::key_code::scroll:
		return CEGUI::Key::ScrollLock;
	case sge::input::keyboard::key_code::pause:
		return CEGUI::Key::Pause;
	case sge::input::keyboard::key_code::lwin:
		return CEGUI::Key::LeftWindows;
	case sge::input::keyboard::key_code::rwin:
		return CEGUI::Key::RightWindows;
	case sge::input::keyboard::key_code::num0:
		return CEGUI::Key::Numpad0;
	case sge::input::keyboard::key_code::num1:
		return CEGUI::Key::Numpad1;
	case sge::input::keyboard::key_code::num2:
		return CEGUI::Key::Numpad2;
	case sge::input::keyboard::key_code::num3:
		return CEGUI::Key::Numpad3;
	case sge::input::keyboard::key_code::num4:
		return CEGUI::Key::Numpad4;
	case sge::input::keyboard::key_code::num5:
		return CEGUI::Key::Numpad5;
	case sge::input::keyboard::key_code::num6:
		return CEGUI::Key::Numpad6;
	case sge::input::keyboard::key_code::num7:
		return CEGUI::Key::Numpad7;
	case sge::input::keyboard::key_code::num8:
		return CEGUI::Key::Numpad8;
	case sge::input::keyboard::key_code::num9:
		return CEGUI::Key::Numpad9;
	case sge::input::keyboard::key_code::numcomma:
		return CEGUI::Key::NumpadComma;
	case sge::input::keyboard::key_code::numenter:
		return CEGUI::Key::NumpadEnter;
	case sge::input::keyboard::key_code::numlock:
		return CEGUI::Key::NumLock;
	case sge::input::keyboard::key_code::add:
		return CEGUI::Key::Add;
	case sge::input::keyboard::key_code::minus:
		return CEGUI::Key::Minus;
	case sge::input::keyboard::key_code::multiply:
		return CEGUI::Key::Multiply;
	case sge::input::keyboard::key_code::divide:
		return CEGUI::Key::Divide;
//	apps:
//	at:
//	ax:
	case sge::input::keyboard::key_code::equals:
		return CEGUI::Key::Equals;
	case sge::input::keyboard::key_code::kana:
		return CEGUI::Key::Kana;
	case sge::input::keyboard::key_code::kanji:
		return CEGUI::Key::Kanji;
	case sge::input::keyboard::key_code::next:
		return CEGUI::Key::Unknown; // TODO
//	noconvert:
	case sge::input::keyboard::key_code::numequals:
		return CEGUI::Key::NumpadEquals;
	case sge::input::keyboard::key_code::period:
		return CEGUI::Key::Unknown; // TODO
//	power:
//	prior:
//	sleep:
//	stop:
//	sysrq:
//	unlabeled:
	case sge::input::keyboard::key_code::yen:
		return CEGUI::Key::Yen;
	case sge::input::keyboard::key_code::unknown:
		return CEGUI::Key::Unknown;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
