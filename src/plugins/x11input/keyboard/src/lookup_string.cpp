/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../lookup_string.hpp"
#include "../char_vector.hpp"
#include "../looked_up_string.hpp"
#include "../translate_key_code.hpp"
#include "../../input_context.hpp"
#include <sge/input/exception.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <X11/extensions/XInput2.h>
#include <X11/Xlib.h>

namespace
{

int
do_lookup(
	sge::x11input::input_context const &_input_context,
	XKeyPressedEvent &_event,
	wchar_t *const _data,
	int const _size,
	KeySym &_key_sym,
	Status &_status
)
{
	return
		::XwcLookupString(
			_input_context.get(),
			&_event,
			_data,
			_size,
			&_key_sym,
			&_status
		);
}

}

sge::x11input::keyboard::looked_up_string const
sge::x11input::keyboard::lookup_string(
	x11input::input_context const &_input_context,
	XIDeviceEvent const &_event
)
{
	KeySym key_sym;

	// HACK HACK
	XKeyPressedEvent xev =
	{
		KeyPress,
		_event.serial,
		_event.send_event,
		_event.display,
		_event.event,
		_event.root,
		_event.child,
		_event.time,
		static_cast<
			int
		>(
			_event.event_x
		),
		static_cast<
			int
		>(
			_event.event_y
		),
		static_cast<
			int
		>(
			_event.root_x
		),
		static_cast<
			int
		>(
			_event.root_y
		),
		static_cast<
			unsigned
		>(
			_event.mods.effective
			|
			((_event.group.effective & 0x3) << 13)
		),
		static_cast<
			unsigned
		>(
			_event.detail
		),
		True // same_screen?
	};

	Status status;

	// first get the size needed
	// FIXME: why can't we read how many chars will be returned?
	int const needed_chars(
		42
	);/*
		::do_lookup(
			_input_context,
			xev,
			NULL,
			0,
			key_sym,
			status
		)
	);*/

	x11input::keyboard::char_vector buffer(
		static_cast<
			x11input::keyboard::char_vector::size_type
		>(
			needed_chars
		)
	);

	int const chars_return(
		::do_lookup(
			_input_context,
			xev,
			buffer.data(),
			static_cast<
				int
			>(
				buffer.size()
			),
			key_sym,
			status
		)
	);

	buffer.resize_uninitialized(
		chars_return
	);

#if 0
	if(
		chars_return != needed_chars
	)
		throw sge::input::exception(
			(
				fcppt::format(
					FCPPT_TEXT("XwcLookupString mismatch of lengths!")
					FCPPT_TEXT(" Expected: %1%, got %2%.")
				)
				% needed_chars
				% chars_return
			).str()
		);
#endif
	switch(
		status
	)
	{
	case XBufferOverflow:
		throw sge::input::exception(
			FCPPT_TEXT("XwcLookupString(): XBufferOverflow!")
		);
	case XLookupChars:
		return
			x11input::keyboard::looked_up_string(
				buffer,
				sge::input::keyboard::key_code::unknown
			);
	case XLookupKeySym:
		return
			x11input::keyboard::looked_up_string(
				x11input::keyboard::char_vector(),
				x11input::keyboard::translate_key_code(
					key_sym
				)
			);
	case XLookupBoth:
		return
			x11input::keyboard::looked_up_string(
				buffer,
				x11input::keyboard::translate_key_code(
					key_sym
				)
			);
	case XLookupNone:
		return
			x11input::keyboard::looked_up_string(
				x11input::keyboard::char_vector(),
				sge::input::keyboard::key_code::unknown
			);
	}

	throw sge::input::exception(
		FCPPT_TEXT("XwcLookupString(): Unknown return value!")
	);
}
