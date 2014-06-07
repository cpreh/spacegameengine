/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/cursor/scroll_code.hpp>
#include <sge/x11input/cursor/scroll_code.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <fcppt/config/external_end.hpp>


sge::input::cursor::scroll_code
sge::x11input::cursor::scroll_code(
	int const _scroll_type
)
{
	switch(
		_scroll_type
	)
	{
	case XIScrollTypeVertical:
		return
			sge::input::cursor::scroll_code::vertical;
	case XIScrollTypeHorizontal:
		return
			sge::input::cursor::scroll_code::horizontal;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
