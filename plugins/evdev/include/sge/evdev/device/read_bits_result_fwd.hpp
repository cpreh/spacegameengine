//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_READ_BITS_RESULT_FWD_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_READ_BITS_RESULT_FWD_HPP_INCLUDED

#include <sge/evdev/device/read_bits_value.hpp>
#include <fcppt/container/bitfield/object_fwd.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

template<
	typename Enum
>
using read_bits_result
=
fcppt::container::bitfield::object<
	Enum,
	sge::evdev::device::read_bits_value
>;

}
}
}

#endif
