//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_FF_CONVERT_VARIANT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_CONVERT_VARIANT_HPP_INCLUDED

#include <sge/evdev/joypad/ff/variant.hpp>
#include <sge/input/joypad/ff/variant_fwd.hpp>


namespace sge::evdev::joypad::ff
{

sge::evdev::joypad::ff::variant
convert_variant(
	sge::input::joypad::ff::variant const &
);

}

#endif
