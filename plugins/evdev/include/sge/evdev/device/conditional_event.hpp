//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_CONDITIONAL_EVENT_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_CONDITIONAL_EVENT_HPP_INCLUDED

#include <sge/evdev/device/event.hpp>
#include <sge/evdev/device/event_type.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/map.hpp>


namespace sge::evdev::device
{

// TODO(philipp): Better typing
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

#endif
