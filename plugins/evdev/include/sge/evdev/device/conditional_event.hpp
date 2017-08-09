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
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/map.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

// TODO: Better typing
template<
	typename Type,
	typename Map,
	typename Info,
	typename Function
>
awl::event::optional_base_unique_ptr
conditional_event(
	fcppt::shared_ptr<
		Type
	> const _ptr,
	sge::evdev::device::event const &_event,
	Map const &_map,
	Info const &_info,
	Function const &_function
)
{
	return
		fcppt::optional::map(
			fcppt::container::find_opt_mapped(
				_map,
				sge::evdev::device::event_type(
					_event.get().code
				)
			),
			[
				_ptr,
				&_function,
				_info,
				_event
			](
				auto const &_mapped
			)
			{
				return
					_function(
						_ptr,
						_mapped.get(),
						_info,
						_event
					);
			}
		);
}

}
}
}

#endif
