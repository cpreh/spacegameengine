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


#include <sge/systems/input.hpp>
#include <sge/systems/detail/input.hpp>


sge::systems::detail::input::input(
	sge::systems::input const &_parameters,
	sge::systems::detail::input::cursor_demuxer const _cursor_demuxer,
	sge::systems::detail::input::keyboard_collector const _keyboard_collector,
	sge::systems::detail::input::mouse_collector const _mouse_collector
)
:
	parameters_(
		_parameters
	),
	cursor_demuxer_(
		_cursor_demuxer
	),
	keyboard_collector_(
		_keyboard_collector
	),
	mouse_collector_(
		_mouse_collector
	)
{
}

sge::systems::input const &
sge::systems::detail::input::parameters() const
{
	return parameters_;
}

sge::systems::detail::input::cursor_demuxer const
sge::systems::detail::input::get_cursor_demuxer() const
{
	return cursor_demuxer_;
}

sge::systems::detail::input::keyboard_collector const
sge::systems::detail::input::get_keyboard_collector() const
{
	return keyboard_collector_;
}

sge::systems::detail::input::mouse_collector const
sge::systems::detail::input::get_mouse_collector() const
{
	return mouse_collector_;
}
