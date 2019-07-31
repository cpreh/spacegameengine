//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_EVENT_TYPE_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_EVENT_TYPE_HPP_INCLUDED

#include <sge/evdev/device/event_type_value.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::evdev::device::event_type_value,
	event_type
);

}
}
}

#endif
