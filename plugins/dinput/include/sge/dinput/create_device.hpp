//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_CREATE_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_CREATE_DEVICE_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/dinput_device_unique_ptr.hpp>


namespace sge
{
namespace dinput
{

sge::dinput::dinput_device_unique_ptr
create_device(
	IDirectInput8 &,
	GUID
);

}
}

#endif
