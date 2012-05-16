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


#include <sge/evdev/joypad/fd_unique_ptr.hpp>
#include <sge/evdev/joypad/fd.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/input/joypad/absolute_axis_callback.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_callback.hpp>
#include <fcppt/move.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>



sge::evdev::joypad::object::object(
	sge::evdev::joypad::fd_unique_ptr _fd,
	sge::input::joypad::info const &_info
)
:
	sge::input::joypad::device(),
	fd_(
		fcppt::move(
			_fd
		)
	),
	info_(
		_info
	),
	absolute_axis_(),
	button_(),
	relative_axis_()
{
}

sge::evdev::joypad::object::~object()
{
}

fcppt::signal::auto_connection
sge::evdev::joypad::object::absolute_axis_callback(
	sge::input::joypad::absolute_axis_callback const &_callback
)
{
	return
		absolute_axis_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::joypad::object::button_callback(
	sge::input::joypad::button_callback const &_callback
)
{
	return
		button_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::joypad::object::relative_axis_callback(
	sge::input::joypad::relative_axis_callback const &_callback
)
{
	return
		relative_axis_.connect(
			_callback
		);
}

sge::input::joypad::info const &
sge::evdev::joypad::object::info() const
{
	return
		info_;
}
