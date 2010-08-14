/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/xcb/screen_iterator.hpp>
#include <sge/xcb/screen.hpp>
#include <sge/xcb/setup.hpp>
#include <xcb/xcb.h>

sge::xcb::screen_iterator::screen_iterator()
:
	iterator_()
{}


sge::xcb::screen_iterator::screen_iterator(
	setup const &setup_
)
:
	iterator_(
		xcb_setup_roots_iterator(
			setup_.get()
		)
	)
{}

sge::xcb::screen_iterator::reference
sge::xcb::screen_iterator::dereference() const
{
	return
		screen(
			iterator_.data
		);
}

void
sge::xcb::screen_iterator::increment()
{
	xcb_screen_next(
		&iterator_
	);
}

bool
sge::xcb::screen_iterator::equal_to(
	screen_iterator const &other_
) const
{
	return iterator_.data == other_.iterator_.data;
}
