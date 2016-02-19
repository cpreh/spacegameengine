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
#include <sge/src/cegui/convert_key.hpp>
#include <sge/src/cegui/optional_key_scan.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/InputEvent.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::optional_key_scan
sge::cegui::convert_key(
	sge::input::key::code const _code
)
{
	switch(
		_code
	)
	{
	case sge::input::key::code::escape:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Escape
			);
	case sge::input::key::code::return_:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Return
			);
	case sge::input::key::code::left_shift:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftShift
			);
	case sge::input::key::code::right_shift:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightShift
			);
	case sge::input::key::code::tab:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Tab
			);
	case sge::input::key::code::backspace:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Backspace
			);
	case sge::input::key::code::left_control:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftControl
			);
	case sge::input::key::code::right_control:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightControl
			);
	case sge::input::key::code::left_alt:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftAlt
			);
	case sge::input::key::code::right_alt:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightAlt
			);
	case sge::input::key::code::space:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Space
			);
	case sge::input::key::code::capital:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Capital
			);
	case sge::input::key::code::insert:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Insert
			);
	case sge::input::key::code::home:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Home
			);
	case sge::input::key::code::pageup:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::PageUp
			);
	case sge::input::key::code::delete_:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Delete
			);
	case sge::input::key::code::end:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::End
			);
	case sge::input::key::code::pagedown:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::PageDown
			);
	case sge::input::key::code::left:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ArrowLeft
			);
	case sge::input::key::code::right:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ArrowRight
			);
	case sge::input::key::code::up:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ArrowUp
			);
	case sge::input::key::code::down:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ArrowDown
			);
	case sge::input::key::code::a:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::A
			);
	case sge::input::key::code::b:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::B
			);
	case sge::input::key::code::c:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::C
			);
	case sge::input::key::code::d:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::D
			);
	case sge::input::key::code::e:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::E
			);
	case sge::input::key::code::f:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F
			);
	case sge::input::key::code::g:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::G
			);
	case sge::input::key::code::h:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::H
			);
	case sge::input::key::code::i:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::I
			);
	case sge::input::key::code::j:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::J
			);
	case sge::input::key::code::k:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::K
			);
	case sge::input::key::code::l:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::L
			);
	case sge::input::key::code::m:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::M
			);
	case sge::input::key::code::n:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::N
			);
	case sge::input::key::code::o:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::O
			);
	case sge::input::key::code::p:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::P
			);
	case sge::input::key::code::q:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Q
			);
	case sge::input::key::code::r:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::R
			);
	case sge::input::key::code::s:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::S
			);
	case sge::input::key::code::t:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::T
			);
	case sge::input::key::code::u:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::U
			);
	case sge::input::key::code::v:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::V
			);
	case sge::input::key::code::w:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::W
			);
	case sge::input::key::code::x:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::X
			);
	case sge::input::key::code::y:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Y
			);
	case sge::input::key::code::z:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Z
			);
	case sge::input::key::code::_0:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Zero
			);
	case sge::input::key::code::_1:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::One
			);
	case sge::input::key::code::_2:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Two
			);
	case sge::input::key::code::_3:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Three
			);
	case sge::input::key::code::_4:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Four
			);
	case sge::input::key::code::_5:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Five
			);
	case sge::input::key::code::_6:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Six
			);
	case sge::input::key::code::_7:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Seven
			);
	case sge::input::key::code::_8:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Eight
			);
	case sge::input::key::code::_9:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Nine
			);
	case sge::input::key::code::f1:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F1
			);
	case sge::input::key::code::f2:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F2
			);
	case sge::input::key::code::f3:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F3
			);
	case sge::input::key::code::f4:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F4
			);
	case sge::input::key::code::f5:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F5
			);
	case sge::input::key::code::f6:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F6
			);
	case sge::input::key::code::f7:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F7
			);
	case sge::input::key::code::f8:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F8
			);
	case sge::input::key::code::f9:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F9
			);
	case sge::input::key::code::f10:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F10
			);
	case sge::input::key::code::f11:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F11
			);
	case sge::input::key::code::f12:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F12
			);
	case sge::input::key::code::f13:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F13
			);
	case sge::input::key::code::f14:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F14
			);
	case sge::input::key::code::f15:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::F15
			);
	case sge::input::key::code::comma:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Comma
			);
	case sge::input::key::code::colon:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Colon
			);
	case sge::input::key::code::decimal:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Decimal
			);
	case sge::input::key::code::apostrophe:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Apostrophe
			);
	case sge::input::key::code::backslash:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Backslash
			);
	case sge::input::key::code::grave:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Grave
			);
	case sge::input::key::code::subtract:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Subtract
			);
	case sge::input::key::code::left_bracket:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftBracket
			);
	case sge::input::key::code::right_bracket:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightBracket
			);
	case sge::input::key::code::semicolon:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Semicolon
			);
	case sge::input::key::code::slash:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Slash
			);
	case sge::input::key::code::underline:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Underline
			);
	case sge::input::key::code::scroll:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::ScrollLock
			);
	case sge::input::key::code::pause:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Pause
			);
	case sge::input::key::code::left_win:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::LeftWindows
			);
	case sge::input::key::code::right_win:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::RightWindows
			);
	case sge::input::key::code::num_0:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad0
			);
	case sge::input::key::code::num_1:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad1
			);
	case sge::input::key::code::num_2:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad2
			);
	case sge::input::key::code::num_3:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad3
			);
	case sge::input::key::code::num_4:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad4
			);
	case sge::input::key::code::num_5:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad5
			);
	case sge::input::key::code::num_6:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad6
			);
	case sge::input::key::code::num_7:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad7
			);
	case sge::input::key::code::num_8:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad8
			);
	case sge::input::key::code::num_9:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Numpad9
			);
	case sge::input::key::code::num_comma:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NumpadComma
			);
	case sge::input::key::code::num_enter:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NumpadEnter
			);
	case sge::input::key::code::num_equals:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NumpadEquals
			);
	case sge::input::key::code::num_lock:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NumLock
			);
	case sge::input::key::code::add:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Add
			);
	case sge::input::key::code::minus:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Minus
			);
	case sge::input::key::code::multiply:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Multiply
			);
	case sge::input::key::code::divide:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Divide
			);
	case sge::input::key::code::apps:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::AppMenu
			);
	case sge::input::key::code::circumflex:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::PrevTrack
			);
	case sge::input::key::code::at:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::At
			);
	case sge::input::key::code::ax:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::AX
			);
	case sge::input::key::code::equals:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Equals
			);
	case sge::input::key::code::kana:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Kana
			);
	case sge::input::key::code::kanji:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Kanji
			);
	case sge::input::key::code::convert:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Convert
			);
	case sge::input::key::code::noconvert:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::NoConvert
			);
	case sge::input::key::code::period:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Period
			);
	case sge::input::key::code::power:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Power
			);
	case sge::input::key::code::sleep:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Sleep
			);
	case sge::input::key::code::stop:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Stop
			);
	case sge::input::key::code::sysrq:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::SysRq
			);
	case sge::input::key::code::unlabeled:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Unlabeled
			);
	case sge::input::key::code::yen:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Yen
			);
	case sge::input::key::code::unknown:
		return
			sge::cegui::optional_key_scan(
				CEGUI::Key::Unknown
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
