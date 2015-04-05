/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GUIContext.h>
#include <CEGUI/InputEvent.h>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::cegui::optional_key_scan const
process_key_code(
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
	fcppt::maybe_void(
		::process_key_code(
			_event.key_code(),
			sge::cegui::convert_key(
				_event.key_code()
			)
		),
		[
			&_event,
			this
		](
			CEGUI::Key::Scan const _scan
		)
		{
			if(
				_event.pressed()
			)
				gui_context_.injectKeyDown(
					_scan
				);
			else
				gui_context_.injectKeyUp(
					_scan
				);
		}
	);
}

void
sge::cegui::syringe::inject(
	sge::input::keyboard::key_repeat_event const &_event
)
{
	fcppt::maybe_void(
		::process_key_code(
			_event.key_code(),
			sge::cegui::convert_key(
				_event.key_code()
			)
		),
		[
			&_event,
			this
		](
			CEGUI::Key::Scan const _scan
		)
		{
			gui_context_.injectKeyDown(
				_scan
			);
		}
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
	>
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
	fcppt::maybe(
		sge::cegui::convert_cursor_button(
			_event.button_code()
		),
		[
			&_event
		]{
			FCPPT_LOG_WARNING(
				local_log,
				fcppt::log::_
					<< FCPPT_TEXT("Warning: got a button which I couldn't process. Its code is: ")
					<< sge::input::cursor::button_code_to_string(
						_event.button_code()
					)
					<< FCPPT_TEXT("; Doing nothing.")
			);
		},
		[
			&_event,
			this
		](
			CEGUI::MouseButton const _button
		)
		{
			if(
				_button
				==
				CEGUI::NoButton
			)
				return;

			if(
				_event.pressed()
			)
				gui_context_.injectMouseButtonDown(
					_button
				);
			else
				gui_context_.injectMouseButtonUp(
					_button
				);
		}
	);
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::move_event const &_event
)
{
	fcppt::maybe_void(
		_event.position(),
		[
			this
		](
			sge::input::cursor::position const _position
		)
		{
			this->inject(
				_position
			);
		}
	);
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::scroll_event const &_event
)
{
	switch(
		_event.code()
	)
	{
	case sge::input::cursor::scroll_code::horizontal:
		break;
	case sge::input::cursor::scroll_code::vertical:
		gui_context_.injectMouseWheelChange(
			fcppt::cast::int_to_float<
				float
			>(
				_event.value()
			)
		);
		break;
	}
}

void
sge::cegui::syringe::inject(
	sge::input::cursor::position const &_cursor_position
)
{
	gui_context_.injectMousePosition(
		fcppt::cast::int_to_float<
			sge::cegui::unit
		>(
			_cursor_position.x()
		),
		fcppt::cast::int_to_float<
			sge::cegui::unit
		>(
			_cursor_position.y()
		)
	);
}

namespace
{

sge::cegui::optional_key_scan const
process_key_code(
	sge::input::keyboard::key_code const _orig_code,
	sge::cegui::optional_key_scan const &_code
)
{
	return
		fcppt::maybe(
			_code,
			[
				_orig_code
			]{
				FCPPT_LOG_WARNING(
					local_log,
					fcppt::log::_
						<< FCPPT_TEXT("Got a key which I couldn't process. Its code is: ")
						<< sge::input::keyboard::key_code_to_string(
							_orig_code
						)
						<< FCPPT_TEXT("; Doing nothing."));

				return
					sge::cegui::optional_key_scan();
			},
			[](
				CEGUI::Key::Scan const _scan
			)
			{
				return
					_scan != CEGUI::Key::Unknown
					?
						sge::cegui::optional_key_scan(
							_scan
						)
					:
						sge::cegui::optional_key_scan()
					;
			}
		);
}

}
