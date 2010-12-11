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


#include "../select_events.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <limits>
#include <X11/extensions/XInput2.h>

void
sge::x11input::select_events(
	awl::backends::x11::window::instance_ptr const _window,
	int const _device,
	x11input::event_id_container const &_events
)
{
	typedef fcppt::container::raw_vector<
		unsigned char
	> raw_container;

	raw_container store(
		_events.size()
		/ std::numeric_limits<unsigned char>::digits
	);

	BOOST_FOREACH(
		x11input::event_id_container::const_reference event,
		_events
	)
		XISetMask(
			store.data(),
			event
		);
	
	XIEventMask mask =
	{
		_device,
		static_cast<
			int
		>(
			store.size()
		),
		store.data()
	};

	if(
		::XISelectEvents(
			_window->display()->get(),
			_window->get(),
			&mask,
			1
		)
		!= Success
	)
		throw sge::input::exception(
			FCPPT_TEXT("XISelectEvents failed!")
		);
}
