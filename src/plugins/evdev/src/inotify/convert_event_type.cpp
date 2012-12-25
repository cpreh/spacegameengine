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


#include <sge/evdev/inotify/convert_event_type.hpp>
#include <sge/evdev/inotify/event_type.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sys/inotify.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


sge::evdev::inotify::event_type
sge::evdev::inotify::convert_event_type(
	std::uint32_t const _mask
)
{
	if(
		_mask & IN_CREATE
	)
		return sge::evdev::inotify::event_type::add;

	if(
		_mask & IN_DELETE
	)
		return sge::evdev::inotify::event_type::remove;

	if(
		_mask & IN_ATTRIB
	)
		return sge::evdev::inotify::event_type::attrib;

	FCPPT_ASSERT_UNREACHABLE;
}
