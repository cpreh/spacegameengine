#include <sge/cegui/detail/input.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_value.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/convert.hpp>
#include <CEGUI/CEGUISystem.h>
#include <boost/bind.hpp>
#include <fcppt/assert.hpp>
#include <map>
#include <iostream>
#include <ostream>

namespace
{
typedef
std::map
<
	sge::input::keyboard::key_code::type,
	CEGUI::uint
>
code_map;

code_map &
keyboard_code_map()
{
	static code_map codes;
	if (!codes.empty())
		return codes;
	codes[sge::input::keyboard::key_code::escape] = CEGUI::Key::Escape;
	codes[sge::input::keyboard::key_code::return_] = CEGUI::Key::Return;
	codes[sge::input::keyboard::key_code::lshift] = CEGUI::Key::LeftShift;
	codes[sge::input::keyboard::key_code::rshift] = CEGUI::Key::RightShift;
	codes[sge::input::keyboard::key_code::tab] = CEGUI::Key::Tab;
	codes[sge::input::keyboard::key_code::backspace] = CEGUI::Key::Backspace;
	codes[sge::input::keyboard::key_code::lctrl] = CEGUI::Key::LeftControl;
	codes[sge::input::keyboard::key_code::rctrl] = CEGUI::Key::RightControl;
	codes[sge::input::keyboard::key_code::alt] = CEGUI::Key::LeftAlt;
	codes[sge::input::keyboard::key_code::altgr] = CEGUI::Key::RightAlt;
	codes[sge::input::keyboard::key_code::space] = CEGUI::Key::Space;
	codes[sge::input::keyboard::key_code::insert] = CEGUI::Key::Insert;
	codes[sge::input::keyboard::key_code::home] = CEGUI::Key::Home;
	codes[sge::input::keyboard::key_code::pageup] = CEGUI::Key::PageUp;
	codes[sge::input::keyboard::key_code::delete_] = CEGUI::Key::Delete;
	codes[sge::input::keyboard::key_code::end] = CEGUI::Key::End;
	codes[sge::input::keyboard::key_code::pagedown] = CEGUI::Key::PageDown;
	codes[sge::input::keyboard::key_code::left] = CEGUI::Key::ArrowLeft;
	codes[sge::input::keyboard::key_code::right] = CEGUI::Key::ArrowRight;
	codes[sge::input::keyboard::key_code::up] = CEGUI::Key::ArrowUp;
	codes[sge::input::keyboard::key_code::down] = CEGUI::Key::ArrowDown;
	codes[sge::input::keyboard::key_code::a] = CEGUI::Key::A;
	codes[sge::input::keyboard::key_code::b] = CEGUI::Key::B;
	codes[sge::input::keyboard::key_code::c] = CEGUI::Key::C;
	codes[sge::input::keyboard::key_code::d] = CEGUI::Key::D;
	codes[sge::input::keyboard::key_code::e] = CEGUI::Key::E;
	codes[sge::input::keyboard::key_code::f] = CEGUI::Key::F;
	codes[sge::input::keyboard::key_code::g] = CEGUI::Key::G;
	codes[sge::input::keyboard::key_code::h] = CEGUI::Key::H;
	codes[sge::input::keyboard::key_code::i] = CEGUI::Key::I;
	codes[sge::input::keyboard::key_code::j] = CEGUI::Key::J;
	codes[sge::input::keyboard::key_code::k] = CEGUI::Key::K;
	codes[sge::input::keyboard::key_code::l] = CEGUI::Key::L;
	codes[sge::input::keyboard::key_code::m] = CEGUI::Key::M;
	codes[sge::input::keyboard::key_code::n] = CEGUI::Key::N;
	codes[sge::input::keyboard::key_code::o] = CEGUI::Key::O;
	codes[sge::input::keyboard::key_code::p] = CEGUI::Key::P;
	codes[sge::input::keyboard::key_code::q] = CEGUI::Key::Q;
	codes[sge::input::keyboard::key_code::r] = CEGUI::Key::R;
	codes[sge::input::keyboard::key_code::s] = CEGUI::Key::S;
	codes[sge::input::keyboard::key_code::t] = CEGUI::Key::T;
	codes[sge::input::keyboard::key_code::u] = CEGUI::Key::U;
	codes[sge::input::keyboard::key_code::v] = CEGUI::Key::V;
	codes[sge::input::keyboard::key_code::w] = CEGUI::Key::W;
	codes[sge::input::keyboard::key_code::x] = CEGUI::Key::X;
	codes[sge::input::keyboard::key_code::y] = CEGUI::Key::Y;
	codes[sge::input::keyboard::key_code::z] = CEGUI::Key::Z;
	codes[sge::input::keyboard::key_code::_0] = CEGUI::Key::Zero;
	codes[sge::input::keyboard::key_code::_1] = CEGUI::Key::One;
	codes[sge::input::keyboard::key_code::_2] = CEGUI::Key::Two;
	codes[sge::input::keyboard::key_code::_3] = CEGUI::Key::Three;
	codes[sge::input::keyboard::key_code::_4] = CEGUI::Key::Four;
	codes[sge::input::keyboard::key_code::_5] = CEGUI::Key::Five;
	codes[sge::input::keyboard::key_code::_6] = CEGUI::Key::Six;
	codes[sge::input::keyboard::key_code::_7] = CEGUI::Key::Seven;
	codes[sge::input::keyboard::key_code::_8] = CEGUI::Key::Eight;
	codes[sge::input::keyboard::key_code::_9] = CEGUI::Key::Nine;
	codes[sge::input::keyboard::key_code::f1] = CEGUI::Key::F1;
	codes[sge::input::keyboard::key_code::f2] = CEGUI::Key::F2;
	codes[sge::input::keyboard::key_code::f3] = CEGUI::Key::F3;
	codes[sge::input::keyboard::key_code::f4] = CEGUI::Key::F4;
	codes[sge::input::keyboard::key_code::f5] = CEGUI::Key::F5;
	codes[sge::input::keyboard::key_code::f6] = CEGUI::Key::F6;
	codes[sge::input::keyboard::key_code::f7] = CEGUI::Key::F7;
	codes[sge::input::keyboard::key_code::f8] = CEGUI::Key::F8;
	codes[sge::input::keyboard::key_code::f9] = CEGUI::Key::F9;
	codes[sge::input::keyboard::key_code::f10] = CEGUI::Key::F10;
	codes[sge::input::keyboard::key_code::f11] = CEGUI::Key::F11;
	codes[sge::input::keyboard::key_code::f12] = CEGUI::Key::F12;
	codes[sge::input::keyboard::key_code::f13] = CEGUI::Key::F13;
	codes[sge::input::keyboard::key_code::f14] = CEGUI::Key::F14;
	codes[sge::input::keyboard::key_code::f15] = CEGUI::Key::F15;
	codes[sge::input::keyboard::key_code::comma] = CEGUI::Key::Comma;
	codes[sge::input::keyboard::key_code::colon] = CEGUI::Key::Colon;
	codes[sge::input::keyboard::key_code::apostrophe] = CEGUI::Key::Apostrophe;
	codes[sge::input::keyboard::key_code::backslash] = CEGUI::Key::Backslash;
	codes[sge::input::keyboard::key_code::grave] = CEGUI::Key::Grave;
	codes[sge::input::keyboard::key_code::substract] = CEGUI::Key::Subtract;
	codes[sge::input::keyboard::key_code::lbracket] = CEGUI::Key::LeftBracket;
	codes[sge::input::keyboard::key_code::rbracket] = CEGUI::Key::RightBracket;
	codes[sge::input::keyboard::key_code::semicolon] = CEGUI::Key::Semicolon;
	codes[sge::input::keyboard::key_code::slash] = CEGUI::Key::Slash;
	codes[sge::input::keyboard::key_code::underline] = CEGUI::Key::Underline;
	codes[sge::input::keyboard::key_code::print] = CEGUI::Key::SysRq;
	codes[sge::input::keyboard::key_code::scroll] = CEGUI::Key::ScrollLock;
	codes[sge::input::keyboard::key_code::pause] = CEGUI::Key::Pause;
	codes[sge::input::keyboard::key_code::lwin] = CEGUI::Key::LeftWindows;
	codes[sge::input::keyboard::key_code::rwin] = CEGUI::Key::RightWindows;
	codes[sge::input::keyboard::key_code::num0] = CEGUI::Key::Numpad0;
	codes[sge::input::keyboard::key_code::num1] = CEGUI::Key::Numpad1;
	codes[sge::input::keyboard::key_code::num2] = CEGUI::Key::Numpad2;
	codes[sge::input::keyboard::key_code::num3] = CEGUI::Key::Numpad3;
	codes[sge::input::keyboard::key_code::num4] = CEGUI::Key::Numpad4;
	codes[sge::input::keyboard::key_code::num5] = CEGUI::Key::Numpad5;
	codes[sge::input::keyboard::key_code::num6] = CEGUI::Key::Numpad6;
	codes[sge::input::keyboard::key_code::num7] = CEGUI::Key::Numpad7;
	codes[sge::input::keyboard::key_code::num8] = CEGUI::Key::Numpad8;
	codes[sge::input::keyboard::key_code::num9] = CEGUI::Key::Numpad9;
	codes[sge::input::keyboard::key_code::numcomma] = CEGUI::Key::NumpadComma;
	//codes[sge::input::keyboard::key_code::numenter] = CEGUI::Key::Numpadenter;
	codes[sge::input::keyboard::key_code::numlock] = CEGUI::Key::NumLock;
	codes[sge::input::keyboard::key_code::add] = CEGUI::Key::Add;
	codes[sge::input::keyboard::key_code::minus] = CEGUI::Key::Minus;
	codes[sge::input::keyboard::key_code::multiply] = CEGUI::Key::Multiply;
	codes[sge::input::keyboard::key_code::divide] = CEGUI::Key::Divide;
	codes[sge::input::keyboard::key_code::equals] = CEGUI::Key::Equals;
	codes[sge::input::keyboard::key_code::kana] = CEGUI::Key::Kana;
	codes[sge::input::keyboard::key_code::kanji] = CEGUI::Key::Kanji;
	//codes[sge::input::keyboard::key_code::next] = CEGUI::Key::Next;
	codes[sge::input::keyboard::key_code::numequals] = CEGUI::Key::NumpadEquals;
	//codes[sge::input::keyboard::key_code::period] = CEGUI::Key::period;
	codes[sge::input::keyboard::key_code::yen] = CEGUI::Key::Yen;
	return codes;
}
}

sge::cegui::detail::input::input(
	sge::input::keyboard::device &_keyboard,
	sge::input::mouse::device &_mouse,
	sge::charconv::system_ptr _charconv_system,
	CEGUI::System &_system)
:
	system_(
		_system),
	charconv_system_(
		_charconv_system),
	key_callback_(
		_keyboard.key_callback(
			boost::bind(
				&input::key_callback,
				this,
				_1))),
	key_repeat_callback_(
		_keyboard.key_repeat_callback(
			boost::bind(
				&input::key_repeat_callback,
				this,
				_1))),
	char_callback_(
		_keyboard.char_callback(
			boost::bind(
				&input::char_callback,
				this,
				_1))),
	mouse_button_callback_(
		_mouse.button_callback(
			boost::bind(
				&input::mouse_button_callback,
				this,
				_1))),
	mouse_axis_callback_(
		_mouse.axis_callback(
			boost::bind(
				&input::mouse_axis_callback,
				this,
				_1)))
{
}

void
sge::cegui::detail::input::update(
	sge::time::funit const delta)
{
	system_.injectTimePulse(
		static_cast<unit>(
			delta));
}

void
sge::cegui::detail::input::key_callback(
	sge::input::keyboard::key_event const &k)
{
	if (keyboard_code_map().find(k.key_code()) == keyboard_code_map().end())
	{
		std::clog 
			<< "Warning: got a key which I couldn't process. Its code is: " 
			<< static_cast<unsigned>(k.key_code()) 
			<< "\nDoing nothing.\n";
		return;
	}

	if (k.pressed())
	{
		system_.injectKeyDown(
			keyboard_code_map()[k.key_code()]);
	}
	else
		system_.injectKeyUp(
			keyboard_code_map()[k.key_code()]);
}

void
sge::cegui::detail::input::key_repeat_callback(
	sge::input::keyboard::key_repeat_event const &k)
{
	if (keyboard_code_map().find(k.key_code()) == keyboard_code_map().end())
	{
		std::clog 
			<< "Warning: got a (repeated) key which I couldn't process. Its code is: " 
			<< static_cast<unsigned>(k.key_code()) 
			<< "\nDoing nothing.\n";
		return;
	}

	system_.injectKeyDown(
		keyboard_code_map()[k.key_code()]);
}

void
sge::cegui::detail::input::char_callback(
	sge::input::keyboard::char_event const &k)
{
	typedef 
	sge::charconv::string_type<sge::charconv::encoding::utf32>::type 
	utf32_string;

	utf32_string const converted_string(
		sge::charconv::convert
		<
			sge::charconv::encoding::utf32, 
			sge::charconv::encoding::wchar
		>(
			charconv_system_,
			std::basic_string<sge::input::keyboard::char_type>(
				1u,
				k.character())));

	FCPPT_ASSERT(
		converted_string.size() == 1);

	system_.injectChar(
		converted_string[0]);
}

void
sge::cegui::detail::input::mouse_button_callback(
	sge::input::mouse::button_event const &e)
{
	typedef
	std::map<sge::input::mouse::button_code::type,CEGUI::MouseButton>
	button_map;

	button_map buttons;
	buttons[sge::input::mouse::button_code::left] = CEGUI::LeftButton;
	buttons[sge::input::mouse::button_code::right] = CEGUI::RightButton;
	buttons[sge::input::mouse::button_code::middle] = CEGUI::MiddleButton;
	// Is this okay?
	buttons[sge::input::mouse::button_code::_4] = CEGUI::X1Button;
	buttons[sge::input::mouse::button_code::_5] = CEGUI::X2Button;

	if (buttons.find(e.button_code()) == buttons.end())
	{
		std::clog 
			<< "Got button event which I couldn't handle. Its code is " 
			<< static_cast<unsigned>(e.button_code())
			<< "\nDoing nothing.\n";
		return;
	}

	if (e.pressed())
		system_.injectMouseButtonDown(
			buttons[e.button_code()]);
	else
		system_.injectMouseButtonUp(
			buttons[e.button_code()]);
}

void
sge::cegui::detail::input::mouse_axis_callback(
	sge::input::mouse::axis_event const &e)
{
	switch (e.axis())
	{
		case sge::input::mouse::axis::x:
			system_.injectMouseMove(
				static_cast<unit>(
					e.axis_value()),
				static_cast<unit>(
					0));
			break;
		case sge::input::mouse::axis::y:
			system_.injectMouseMove(
				static_cast<unit>(
					0),
				static_cast<unit>(
					e.axis_value()));
			break;
		case sge::input::mouse::axis::unknown:
			break;
	}
}
