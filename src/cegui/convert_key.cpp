/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/src/cegui/optional_key_scan.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/InputEvent.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::optional_key_scan const
sge::cegui::convert_key(
	sge::input::keyboard::key_code const _code
)
{
	switch(
		_code
	)
	{
	case sge::input::keyboard::key_code::escape:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Escape
			);
	case sge::input::keyboard::key_code::return_:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Return
			);
	case sge::input::keyboard::key_code::left_shift:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftShift
			);
	case sge::input::keyboard::key_code::right_shift:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightShift
			);
	case sge::input::keyboard::key_code::tab:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Tab
			);
	case sge::input::keyboard::key_code::backspace:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Backspace
			);
	case sge::input::keyboard::key_code::left_control:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftControl
			);
	case sge::input::keyboard::key_code::right_control:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightControl
			);
	case sge::input::keyboard::key_code::left_alt:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftAlt
			);
	case sge::input::keyboard::key_code::right_alt:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightAlt
			);
	case sge::input::keyboard::key_code::space:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Space
			);
	case sge::input::keyboard::key_code::capital:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Capital
			);
	case sge::input::keyboard::key_code::insert:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Insert
			);
	case sge::input::keyboard::key_code::home:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Home
			);
	case sge::input::keyboard::key_code::pageup:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::PageUp
			);
	case sge::input::keyboard::key_code::delete_:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Delete
			);
	case sge::input::keyboard::key_code::end:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::End
			);
	case sge::input::keyboard::key_code::pagedown:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::PageDown
			);
	case sge::input::keyboard::key_code::left:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ArrowLeft
			);
	case sge::input::keyboard::key_code::right:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ArrowRight
			);
	case sge::input::keyboard::key_code::up:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ArrowUp
			);
	case sge::input::keyboard::key_code::down:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ArrowDown
			);
	case sge::input::keyboard::key_code::a:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::A
			);
	case sge::input::keyboard::key_code::b:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::B
			);
	case sge::input::keyboard::key_code::c:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::C
			);
	case sge::input::keyboard::key_code::d:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::D
			);
	case sge::input::keyboard::key_code::e:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::E
			);
	case sge::input::keyboard::key_code::f:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F
			);
	case sge::input::keyboard::key_code::g:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::G
			);
	case sge::input::keyboard::key_code::h:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::H
			);
	case sge::input::keyboard::key_code::i:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::I
			);
	case sge::input::keyboard::key_code::j:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::J
			);
	case sge::input::keyboard::key_code::k:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::K
			);
	case sge::input::keyboard::key_code::l:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::L
			);
	case sge::input::keyboard::key_code::m:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::M
			);
	case sge::input::keyboard::key_code::n:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::N
			);
	case sge::input::keyboard::key_code::o:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::O
			);
	case sge::input::keyboard::key_code::p:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::P
			);
	case sge::input::keyboard::key_code::q:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Q
			);
	case sge::input::keyboard::key_code::r:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::R
			);
	case sge::input::keyboard::key_code::s:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::S
			);
	case sge::input::keyboard::key_code::t:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::T
			);
	case sge::input::keyboard::key_code::u:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::U
			);
	case sge::input::keyboard::key_code::v:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::V
			);
	case sge::input::keyboard::key_code::w:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::W
			);
	case sge::input::keyboard::key_code::x:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::X
			);
	case sge::input::keyboard::key_code::y:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Y
			);
	case sge::input::keyboard::key_code::z:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Z
			);
	case sge::input::keyboard::key_code::_0:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Zero
			);
	case sge::input::keyboard::key_code::_1:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::One
			);
	case sge::input::keyboard::key_code::_2:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Two
			);
	case sge::input::keyboard::key_code::_3:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Three
			);
	case sge::input::keyboard::key_code::_4:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Four
			);
	case sge::input::keyboard::key_code::_5:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Five
			);
	case sge::input::keyboard::key_code::_6:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Six
			);
	case sge::input::keyboard::key_code::_7:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Seven
			);
	case sge::input::keyboard::key_code::_8:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Eight
			);
	case sge::input::keyboard::key_code::_9:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Nine
			);
	case sge::input::keyboard::key_code::f1:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F1
			);
	case sge::input::keyboard::key_code::f2:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F2
			);
	case sge::input::keyboard::key_code::f3:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F3
			);
	case sge::input::keyboard::key_code::f4:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F4
			);
	case sge::input::keyboard::key_code::f5:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F5
			);
	case sge::input::keyboard::key_code::f6:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F6
			);
	case sge::input::keyboard::key_code::f7:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F7
			);
	case sge::input::keyboard::key_code::f8:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F8
			);
	case sge::input::keyboard::key_code::f9:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F9
			);
	case sge::input::keyboard::key_code::f10:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F10
			);
	case sge::input::keyboard::key_code::f11:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F11
			);
	case sge::input::keyboard::key_code::f12:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F12
			);
	case sge::input::keyboard::key_code::f13:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F13
			);
	case sge::input::keyboard::key_code::f14:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F14
			);
	case sge::input::keyboard::key_code::f15:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F15
			);
	case sge::input::keyboard::key_code::comma:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Comma
			);
	case sge::input::keyboard::key_code::colon:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Colon
			);
	case sge::input::keyboard::key_code::decimal:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Decimal
			);
	case sge::input::keyboard::key_code::apostrophe:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Apostrophe
			);
	case sge::input::keyboard::key_code::backslash:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Backslash
			);
	case sge::input::keyboard::key_code::grave:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Grave
			);
	case sge::input::keyboard::key_code::subtract:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Subtract
			);
	case sge::input::keyboard::key_code::left_bracket:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftBracket
			);
	case sge::input::keyboard::key_code::right_bracket:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightBracket
			);
	case sge::input::keyboard::key_code::semicolon:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Semicolon
			);
	case sge::input::keyboard::key_code::slash:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Slash
			);
	case sge::input::keyboard::key_code::underline:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Underline
			);
	case sge::input::keyboard::key_code::scroll:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ScrollLock
			);
	case sge::input::keyboard::key_code::pause:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Pause
			);
	case sge::input::keyboard::key_code::left_win:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftWindows
			);
	case sge::input::keyboard::key_code::right_win:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightWindows
			);
	case sge::input::keyboard::key_code::num_0:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad0
			);
	case sge::input::keyboard::key_code::num_1:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad1
			);
	case sge::input::keyboard::key_code::num_2:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad2
			);
	case sge::input::keyboard::key_code::num_3:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad3
			);
	case sge::input::keyboard::key_code::num_4:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad4
			);
	case sge::input::keyboard::key_code::num_5:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad5
			);
	case sge::input::keyboard::key_code::num_6:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad6
			);
	case sge::input::keyboard::key_code::num_7:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad7
			);
	case sge::input::keyboard::key_code::num_8:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad8
			);
	case sge::input::keyboard::key_code::num_9:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad9
			);
	case sge::input::keyboard::key_code::num_comma:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NumpadComma
			);
	case sge::input::keyboard::key_code::num_enter:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NumpadEnter
			);
	case sge::input::keyboard::key_code::num_equals:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NumpadEquals
			);
	case sge::input::keyboard::key_code::num_lock:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NumLock
			);
	case sge::input::keyboard::key_code::add:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Add
			);
	case sge::input::keyboard::key_code::minus:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Minus
			);
	case sge::input::keyboard::key_code::multiply:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Multiply
			);
	case sge::input::keyboard::key_code::divide:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Divide
			);
	case sge::input::keyboard::key_code::apps:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::AppMenu
			);
	case sge::input::keyboard::key_code::circumflex:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::PrevTrack
			);
	case sge::input::keyboard::key_code::at:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::At
			);
	case sge::input::keyboard::key_code::ax:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::AX
			);
	case sge::input::keyboard::key_code::equals:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Equals
			);
	case sge::input::keyboard::key_code::kana:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Kana
			);
	case sge::input::keyboard::key_code::kanji:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Kanji
			);
	case sge::input::keyboard::key_code::convert:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Convert
			);
	case sge::input::keyboard::key_code::noconvert:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NoConvert
			);
	case sge::input::keyboard::key_code::period:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Period
			);
	case sge::input::keyboard::key_code::power:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Power
			);
	case sge::input::keyboard::key_code::sleep:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Sleep
			);
	case sge::input::keyboard::key_code::stop:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Stop
			);
	case sge::input::keyboard::key_code::sysrq:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::SysRq
			);
	case sge::input::keyboard::key_code::unlabeled:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Unlabeled
			);
	case sge::input::keyboard::key_code::yen:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Yen
			);
	case sge::input::keyboard::key_code::unknown:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Unknown
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
