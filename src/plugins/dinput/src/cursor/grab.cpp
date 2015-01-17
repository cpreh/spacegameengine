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


#include <sge/dinput/cursor/clip.hpp>
#include <sge/dinput/cursor/grab.hpp>
#include <sge/dinput/cursor/set_capture.hpp>
#include <sge/dinput/cursor/show.hpp>
#include <awl/backends/windows/optional_rect.hpp>
#include <awl/backends/windows/window/get_rect.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>


bool
sge::dinput::cursor::grab(
	awl::backends::windows::window::object &_window
)
{
	sge::dinput::cursor::show(
		false
	);

	{
		// When can this fail?
		awl::backends::windows::optional_rect const window_rect(
			awl::backends::windows::window::get_rect(
				_window
			)
		);

		if(
			!window_rect
		)
			return false;

		if(
			!sge::dinput::cursor::clip(
				window_rect
			)
		)
			return false;
	}

	sge::dinput::cursor::set_capture(
		_window
	);

	return true;
}
