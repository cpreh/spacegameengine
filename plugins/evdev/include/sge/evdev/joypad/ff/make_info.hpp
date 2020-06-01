//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_FF_MAKE_INFO_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_MAKE_INFO_HPP_INCLUDED

#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/input/joypad/ff/type_field.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace ff
{

sge::input::joypad::ff::type_field
make_info(
	sge::evdev::device::fd & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}
}
}
}

#endif
