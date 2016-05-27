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


#include <sge/wlinput/focus/holder.hpp>
#include <awl/backends/wayland/seat.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <fcppt/config/external_end.hpp>


sge::wlinput::focus::holder::holder(
	awl::backends::wayland::seat const &_seat
)
:
	impl_{
		::wl_seat_get_keyboard(
			_seat.get()
		)
	}
{
	FCPPT_ASSERT_ERROR(
		impl_
		!=
		nullptr
	);
}

sge::wlinput::focus::holder::~holder()
{
	::wl_keyboard_release(
		impl_
	);
}

wl_keyboard *
sge::wlinput::focus::holder::get() const
{
	return
		impl_;
}
