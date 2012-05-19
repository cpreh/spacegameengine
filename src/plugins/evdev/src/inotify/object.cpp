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


#include <sge/evdev/inotify/object.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/x11/event/fd/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sys/inotify.h>
#include <fcppt/config/external_end.hpp>


sge::evdev::inotify::object::object()
:
	fd_(
		::inotify_init()
	)
{
	if(
		fd_.get()
		==
		-1
	)
		throw sge::input::exception(
			FCPPT_TEXT("inotify_init failed")
		);
}

sge::evdev::inotify::object::~object()
{
	::close(
		fd_.get()
	);
}

awl::backends::x11::event::fd::object const
sge::evdev::inotify::object::fd() const
{
	return
		fd_;
}
