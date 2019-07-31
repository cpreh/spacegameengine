//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_SHARED_PTR_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_SHARED_PTR_HPP_INCLUDED

#include <sge/evdev/joypad/object_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{

typedef
fcppt::shared_ptr<
	sge::evdev::joypad::object
>
shared_ptr;

}
}
}

#endif
