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


#include "../event_data.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>
#include <X11/Xlib.h>

sge::x11input::device::event_data::event_data(
	awl::backends::x11::display_ptr const _display,
	awl::backends::x11::system::event::object const &_event
)
:
	display_(
		_display
	),
	store_(
		_event.get()
	)
{
	if(
		::XGetEventData(
			display_->get(),
			&store_
		)
		== False
	)
		throw sge::input::exception(
			FCPPT_TEXT("XGetEventData failed!")
		);
}

sge::x11input::device::event_data::~event_data()
{
	::XFreeEventData(
		display_->get(),
		&store_
	);
}

void const *
sge::x11input::device::event_data::data() const
{
	return store_.data;
}
