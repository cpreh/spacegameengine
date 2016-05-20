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


#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/wlinput/cursor/object.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


sge::wlinput::cursor::object::object(
	awl::backends::wayland::seat const &_seat
)
:
	sge::input::cursor::object(),
	position_{},
	button_signal_{},
	move_signal_{},
	scroll_signal_{}
{
}

sge::wlinput::cursor::object::~object()
{
}

fcppt::signal::auto_connection
sge::wlinput::cursor::object::button_callback(
	sge::input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::cursor::object::move_callback(
	sge::input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::cursor::object::scroll_callback(
	sge::input::cursor::scroll_callback const &_callback
)
{
	return
		scroll_signal_.connect(
			_callback
		);
}

sge::input::cursor::optional_position
sge::wlinput::cursor::object::position() const
{
	return
		position_;
}

void
sge::wlinput::cursor::object::mode(
	sge::input::cursor::mode const _mode
)
{
}
