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


#include <sge/cegui/syringe.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/input/cursor/button_code_to_string.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/scroll_event.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_code_to_string.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/src/cegui/convert_cursor_button.hpp>
#include <sge/src/cegui/convert_key.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/optional_key_scan.hpp>
#include <sge/src/cegui/optional_mouse_button.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GUIContext.h>
#include <CEGUI/InputEvent.h>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

bool
process_code(
	sge::input::keyboard::key_code,
	sge::cegui::optional_key_scan const &
);

}

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("syringe")
)

sge::cegui::syringe::syringe(
	sge::cegui::system &_system
)
:
	gui_context_(
		_system.gui_context()
	)
{
}

sge::cegui::syringe::~syringe()
{
}

void
sge::cegui::syringe::inject(
	sge::input::keyboard::key_event const &_event
)
{
	sge::cegui::optional_key_scan const code(
		sge::cegui::convert_key(
			_event.key_code()
		)
	);

	if(
		!::process_code(
			_event.key_code(),
			code
		)
	)
		return;

	if(
		_event.pressed()
	)
		gui_context_.injectKeyDown(
			*code
		);
	else
		gui_context_.injectKeyUp(
			*code
		);
}

void
sge::cegui::syringe::inject(
	sge::input::keyboard::key_repeat_event const &_event
)
{
	sge::cegui::optional_key_scan const code(
		sge::cegui::convert_key(
			_event.key_code()
		)
	);

	if(
		!::process_code(
			_event.key_code(),
			code
		)
	)
		return;

	gui_context_.injectKeyDown(
		*code
	);
}

void
sge::cegui::syringe::inject(
	sge::input::keyboard::char_event const &_event
)
{
	typedef
	sge::charconv::string_type<
		sge::charconv::encoding::utf32
	>::type
	utf32_string;

	utf32_string const converted_string(
		sge::charconv::convert
		<
			sge::charconv::encoding::utf32,
			sge::charconv::encoding::wchar
		>(
			std::basic_string<
				sge::input::keyboard::char_type
			>(
				1u,
				_event.character()
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		converted_string.size() == 1
	);

	gui_context_.injectChar(
		converted_string[0]
	);
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::button_event const &_event
)
{
	sge::cegui::optional_mouse_button const code(
		sge::cegui::convert_cursor_button(
			_event.button_code()
		)
	);

	if(
		!code
	)
	{
		FCPPT_LOG_WARNING(
			local_log,
			fcppt::log::_
				<< FCPPT_TEXT("Warning: got a button which I couldn't process. Its code is: ")
				<< sge::input::cursor::button_code_to_string(
					_event.button_code()
				)
				<< FCPPT_TEXT("; Doing nothing."));
		return;
	}

	if(
		*code == CEGUI::NoButton
	)
		return;

	if(
		_event.pressed()
	)
		gui_context_.injectMouseButtonDown(
			*code
		);
	else
		gui_context_.injectMouseButtonUp(
			*code
		);
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::move_event const &_event
)
{
	if(
		_event.position()
	)
		this->inject(
			*_event.position()
		);
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::scroll_event const &_event
)
{
	switch(_event.code())
	{
	case sge::input::cursor::scroll_code::horizontal:
		break;
	case sge::input::cursor::scroll_code::vertical:
		gui_context_.injectMouseWheelChange(
			static_cast<float>(
				_event.value()));
		break;
	}
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::position const &_cursor_position
)
{
	gui_context_.injectMousePosition(
		static_cast<
			sge::cegui::unit
		>(
			_cursor_position.x()
		),
		static_cast<
			sge::cegui::unit
		>(
			_cursor_position.y()
		)
	);
}

namespace
{

bool
process_code(
	sge::input::keyboard::key_code const _orig_code,
	sge::cegui::optional_key_scan const &_code
)
{
	if(
		!_code
	)
	{
		FCPPT_LOG_WARNING(
			local_log,
			fcppt::log::_
				<< FCPPT_TEXT("Got a key which I couldn't process. Its code is: ")
				<< sge::input::keyboard::key_code_to_string(
					_orig_code
				)
				<< FCPPT_TEXT("; Doing nothing."));

		return false;
	}

	return
		*_code != CEGUI::Key::Unknown;
}

}
