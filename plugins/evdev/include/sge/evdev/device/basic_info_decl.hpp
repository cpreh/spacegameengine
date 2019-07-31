//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_BASIC_INFO_DECL_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_BASIC_INFO_DECL_HPP_INCLUDED

#include <sge/evdev/device/basic_info_fwd.hpp>
#include <sge/evdev/device/event_map.hpp>
#include <sge/input/info/container.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

template<
	typename Id,
	typename Info
>
class basic_info
{
public:
	typedef
	sge::input::info::container<
		Id,
		Info
	>
	info_container;

	typedef
	Id
	id;

	typedef
	sge::evdev::device::event_map<
		id
	>
	event_map_type;

	basic_info(
		info_container const &,
		event_map_type const &
	);

	info_container const &
	infos() const;

	event_map_type const &
	event_map() const;
private:
	info_container infos_;

	event_map_type event_map_;
};

}
}
}

#endif
