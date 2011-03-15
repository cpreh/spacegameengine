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


#include "../cursor_confine.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/windows/window/client_rect.hpp>
#include <awl/backends/windows/window/client_rect_to_screen.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

namespace
{

typedef fcppt::optional<
	RECT
> optional_rect;

void
clip_cursor(
	optional_rect _rect
)
{
	if(
		::ClipCursor(
			_rect
			?
				NULL
			:
				&*_rect
		)
		== FALSE
	)
		throw sge::input::exception(
			FCPPT_TEXT("ClipCursor() failed!")
		);
}

}

sge::dinput::cursor_confine::cursor_confine(
	awl::backends::windows::window::instance &_window
)
{
	clip_cursor(
		awl::backends::windows::window::client_rect_to_screen(
			_window,
			awl::backends::windows::window::client_rect(
				_window
			)
		)
	);
}

sge::dinput::cursor_confine::~cursor_confine()
{
	clip_cursor(
		optional_rect()
	);
}
