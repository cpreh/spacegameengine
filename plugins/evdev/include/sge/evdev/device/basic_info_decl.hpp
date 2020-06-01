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
	using
	info_container
	=
	sge::input::info::container<
		Id,
		Info
	>;

	using
	id
	=
	Id;

	using
	event_map_type
	=
	sge::evdev::device::event_map<
		id
	>;

	basic_info(
		info_container &&,
		event_map_type &&
	);

	[[nodiscard]]
	info_container const &
	infos() const;

	[[nodiscard]]
	info_container &
	infos();

	[[nodiscard]]
	event_map_type const &
	event_map() const;

	[[nodiscard]]
	event_map_type &
	event_map();
private:
	info_container infos_;

	event_map_type event_map_;
};

}
}
}

#endif
