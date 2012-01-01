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


#include <sge/cegui/syringe.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/src/cegui/cursor_button_translation.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/keyboard_code_translation.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIInputEvent.h>
#include <CEGUISystem.h>
#include <string>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("syringe"))

sge::cegui::syringe::syringe(
	system &_system)
:
	system_(
		_system),
	charconv_system_(
		system_.charconv_system())
{
}

void
sge::cegui::syringe::inject(
	sge::input::keyboard::key_event const &k)
{
	if (keyboard_code_translation().find(k.key_code()) == keyboard_code_translation().end())
	{
		FCPPT_LOG_WARNING(
			local_log,
			fcppt::log::_
				<< FCPPT_TEXT("Warning: got a key which I couldn't process. Its code is: ")
				<< static_cast<unsigned>(k.key_code())
				<< FCPPT_TEXT("; Doing nothing."));
		return;
	}

	if (k.pressed())
	{
		CEGUI::System::getSingleton().injectKeyDown(
			keyboard_code_translation()[k.key_code()]);
	}
	else
	{
		CEGUI::System::getSingleton().injectKeyUp(
			keyboard_code_translation()[k.key_code()]);
	}
}

void
sge::cegui::syringe::inject(
	sge::input::keyboard::key_repeat_event const &k)
{
	if (keyboard_code_translation().find(k.key_code()) == keyboard_code_translation().end())
	{
		FCPPT_LOG_WARNING(
			local_log,
			fcppt::log::_
				<< FCPPT_TEXT("Warning: got a key which I couldn't process. Its code is: ")
				<< static_cast<unsigned>(k.key_code())
				<< FCPPT_TEXT("; Doing nothing."));
		return;
	}

	CEGUI::System::getSingleton().injectKeyDown(
		keyboard_code_translation()[k.key_code()]);
}

void
sge::cegui::syringe::inject(
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

	FCPPT_ASSERT_ERROR(
		converted_string.size() == 1);

	CEGUI::System::getSingleton().injectChar(
		converted_string[0]);
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::button_event const &e)
{
	if (cursor_button_translation().find(e.button_code()) == cursor_button_translation().end())
	{
		FCPPT_LOG_WARNING(
			local_log,
			fcppt::log::_
				<< FCPPT_TEXT("Warning: got a button which I couldn't process. Its code is: ")
				<< static_cast<unsigned>(e.button_code())
				<< FCPPT_TEXT("; Doing nothing."));
		return;
	}

	if (e.pressed())
		CEGUI::System::getSingleton().injectMouseButtonDown(
			cursor_button_translation()[e.button_code()]);
	else
		CEGUI::System::getSingleton().injectMouseButtonUp(
			cursor_button_translation()[e.button_code()]);
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::move_event const &e)
{
	if(
		e.position()
	)
		inject(
			*e.position());
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::position const &cursor_position)
{
	CEGUI::System::getSingleton().injectMousePosition(
		static_cast<unit>(
			cursor_position.x()),
		static_cast<unit>(
			cursor_position.y()));
}
