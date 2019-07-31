//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_DEVICE_ENUMERATE_OBJECTS_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_ENUMERATE_OBJECTS_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerator_fwd.hpp>


namespace sge
{
namespace dinput
{
namespace device
{

void
enumerate_objects(
	IDirectInputDevice8 &,
	sge::dinput::device::enumerator &,
	DWORD flags
);

}
}
}

#endif
