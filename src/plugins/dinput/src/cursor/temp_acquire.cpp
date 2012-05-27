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


#include <awl/backends/windows/event/type.hpp>
#include <sge/dinput/cursor/temp_acquire.hpp>


sge::dinput::cursor::temp_acquire::temp_acquire(
	bool const _was_acquired,
	awl::backends::windows::event::type const _event_type
)
:
	was_acquired_(
		_was_acquired
	),
	event_type_(
		_event_type
	)
{
}

sge::dinput::cursor::temp_acquire::~temp_acquire()
{
}

bool
sge::dinput::cursor::temp_acquire::needs_acquire(
	awl::backends::windows::event::type const _event_type
) const
{
	return
		was_acquired_
		&&
		event_type_ == _event_type;
}
