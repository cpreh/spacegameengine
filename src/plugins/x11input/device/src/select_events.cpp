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
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <limits>
#include <X11/extensions/XInput2.h>

void
sge::x11input::device::select_events(
	awl::backends::x11::window::instance_ptr const _window,
	x11input::device::id const _device,
	x11input::device::event_id_container const &_events
)
{
	if(
		_events.empty()
	)
		return;

	typedef unsigned char bit_type;

	typedef fcppt::container::raw_vector<
		bit_type
	> raw_container;

	raw_container store(
		fcppt::math::ceil_div(
			static_cast<
				raw_container::size_type
			>(
				*std::max_element(
					_events.begin(),
					_events.end()
				)
			),
			static_cast<
				raw_container::size_type
			>(
				std::numeric_limits<
					bit_type
				>::digits
			)
		),
		static_cast<
			bit_type
		>(0)
	);

	BOOST_FOREACH(
		x11input::device::event_id_container::const_reference event,
		_events
	)
		XISetMask(
			store.data(),
			event.get()
		);
	
	XIEventMask mask =
	{
		_device.get(),
		static_cast<
			int
		>(
			store.size()
		),
		store.data()
	};

	if(
		std::count(
			_events.begin(),
			_events.end(),
			XI_RawMotion
		)
	)
		::XISelectEvents(
			_window->display()->get(),
			XRootWindow(
				_window->display()->get(),
				0
			),
			&mask,
			1
		);
	else
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
