//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_ENUM_DEVICES_HPP_INCLUDED
#define SGE_DINPUT_ENUM_DEVICES_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/enum_devices_function.hpp>

namespace sge
{
namespace dinput
{

void enum_devices(IDirectInput8 &, sge::dinput::enum_devices_function, void *);

}
}

#endif
