//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_FF_VARIANT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_VARIANT_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace ff
{

typedef
decltype(
	ff_effect::u
)
variant;

}
}
}
}

#endif
