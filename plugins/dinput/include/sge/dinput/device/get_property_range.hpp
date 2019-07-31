//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_DEVICE_GET_PROPERTY_RANGE_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_GET_PROPERTY_RANGE_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/range_fwd.hpp>


namespace sge
{
namespace dinput
{
namespace device
{

sge::dinput::device::range const
get_property_range(
	IDirectInputDevice8 &,
	DIDEVICEOBJECTINSTANCE const &,
	REFGUID
);

}
}
}

#endif
