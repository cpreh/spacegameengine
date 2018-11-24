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


#include <sge/input/exception.hpp>
#include <sge/x11input/cursor/create_grab.hpp>
#include <sge/x11input/cursor/grab.hpp>
#include <sge/x11input/cursor/optional_grab_unique_ptr.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/cursor/object_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>


sge::x11input::cursor::optional_grab_unique_ptr
sge::x11input::cursor::create_grab(
	fcppt::log::object &_log,
	awl::backends::x11::window::base const &_window,
	sge::x11input::device::id const _id,
	awl::backends::x11::cursor::object const &_cursor
)
try
{
	return
		sge::x11input::cursor::optional_grab_unique_ptr{
			fcppt::make_unique_ptr<
				sge::x11input::cursor::grab
			>(
				_window,
				_id,
				_cursor
			)
		};
}
catch(
	sge::input::exception const &_error
)
{
	FCPPT_LOG_ERROR(
		_log,
		fcppt::log::out
			<<
			_error.string()
	)

	return
		sge::x11input::cursor::optional_grab_unique_ptr{};
}
