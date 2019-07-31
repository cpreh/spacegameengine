//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_READ_BITS_RESULT_FWD_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_READ_BITS_RESULT_FWD_HPP_INCLUDED

#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/device/read_bits_value.hpp>
#include <fcppt/container/bitfield/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

template<
	sge::evdev::device::event_type_value Count
>
using read_bits_result
=
fcppt::container::bitfield::object<
	sge::evdev::device::event_type_value,
	std::integral_constant<
		sge::evdev::device::event_type_value,
		Count
	>,
	sge::evdev::device::read_bits_value
>;

}
}
}

#endif
