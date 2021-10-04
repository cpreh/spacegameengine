//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_EVENT_MAP_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_EVENT_MAP_HPP_INCLUDED

#include <sge/evdev/device/event_type.hpp>
#include <fcppt/strong_typedef_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge::evdev::device
{

template<
	typename Id
>
using
event_map
=
std::unordered_map<
	sge::evdev::device::event_type,
	Id
>;

}

#endif
