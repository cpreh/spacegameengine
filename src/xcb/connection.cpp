/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/xcb/connection.hpp>
#include <fcppt/to_std_string.hpp>
#include <xcb/xcb.h>

namespace
{

void
check_connection(
	xcb_connection_t *const connection_
)
{
}

}

sge::xcb::connection::connection()
:
	screen_(
		0
	),
	connection_(
		xcb_connect(
			NULL,
			&screen_
		)
	)
{
	check_connection(
		connection_
	);
}


sge::xcb::connection::connection(
	string const &display_,
	screen _screen
)
:
	screen_(_screen),
	connection_(
		xcb_connect(
			fcppt::to_std_string(
				display_
			).c_str(),
			&screen_
		)
	)
{
	check_connection(
		connection_
	);
}

xcb_connection_t *
sge::xcb::connection::get() const
{
	return connection_;
}

sge::xcb::connection::~connection()
{
	xcb_disconnect(
		connection_
	);
}
