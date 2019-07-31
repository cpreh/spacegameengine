//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_OPTIONAL_ITERATOR_FWD_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_OPTIONAL_ITERATOR_FWD_HPP_INCLUDED

#include <sge/evdev/joypad/map.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{

typedef
fcppt::optional::object<
	sge::evdev::joypad::map::iterator
>
optional_iterator;

}
}
}

#endif
