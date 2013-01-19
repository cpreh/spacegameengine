/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/evdev/inotify/event.hpp>
#include <sge/evdev/inotify/event_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::evdev::inotify::event::event(
	boost::filesystem::path const &_filename,
	sge::evdev::inotify::event_type const _event_type
)
:
	filename_(
		_filename
	),
	event_type_(
		_event_type
	)
{
}

boost::filesystem::path const &
sge::evdev::inotify::event::filename() const
{
	return
		filename_;
}

sge::evdev::inotify::event_type
sge::evdev::inotify::event::event_type() const
{
	return
		event_type_;
}
