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


#ifndef SGE_EVDEV_DEVICE_CONDITIONAL_EVENT_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_CONDITIONAL_EVENT_HPP_INCLUDED

#include <sge/evdev/device/event.hpp>
#include <sge/evdev/device/event_type.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

template<
	typename Signal,
	typename Map,
	typename Info,
	typename Function
>
void
conditional_event(
	sge::evdev::device::event const &_event,
	Signal &_signal,
	Map const &_map,
	Info const &_info,
	Function const &_function
)
{
	typename Map::const_iterator const it(
		_map.find(
			sge::evdev::device::event_type(
				_event.get().code
			)
		)
	);

	if(
		it == _map.end()
	)
		return;

	_signal(
		_function(
			it->second,
			_info,
			_event
		)
	);
}

}
}
}

#endif
