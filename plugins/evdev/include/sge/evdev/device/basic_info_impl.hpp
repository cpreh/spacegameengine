//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_BASIC_INFO_IMPL_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_BASIC_INFO_IMPL_HPP_INCLUDED

#include <sge/evdev/device/basic_info_decl.hpp>


template<
	typename Id,
	typename Info
>
sge::evdev::device::basic_info<
	Id,
	Info
>::basic_info(
	info_container const &_infos,
	event_map_type const &_event_map
)
:
	infos_(
		_infos
	),
	event_map_(
		_event_map
	)
{
}

template<
	typename Id,
	typename Info
>
typename
sge::evdev::device::basic_info<
	Id,
	Info
>::info_container const &
sge::evdev::device::basic_info<
	Id,
	Info
>::infos() const
{
	return
		infos_;
}

template<
	typename Id,
	typename Info
>
typename
sge::evdev::device::basic_info<
	Id,
	Info
>::info_container &
sge::evdev::device::basic_info<
	Id,
	Info
>::infos()
{
	return
		infos_;
}

template<
	typename Id,
	typename Info
>
typename
sge::evdev::device::basic_info<
	Id,
	Info
>::event_map_type const &
sge::evdev::device::basic_info<
	Id,
	Info
>::event_map() const
{
	return
		event_map_;
}

template<
	typename Id,
	typename Info
>
typename
sge::evdev::device::basic_info<
	Id,
	Info
>::event_map_type &
sge::evdev::device::basic_info<
	Id,
	Info
>::event_map()
{
	return
		event_map_;
}

#endif
